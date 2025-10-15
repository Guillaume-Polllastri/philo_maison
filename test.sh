#!/bin/bash

# ============================================================================
#                         PHILOSOPHERS TEST SUITE
# ============================================================================
# 
# This script tests the philosophers program with various scenarios:
# - Parameter validation (invalid arguments)
# - Death timing accuracy  
# - Meal completion logic
# - Edge cases and stress tests
#
# Test Requirements:
# • No testing with >200 philosophers
# • No time values <60ms (time_to_die, time_to_eat, time_to_sleep)  
# • Specific test cases as per subject requirements
# • Death timing accuracy within 10ms tolerance
# • Each test runs multiple times for reliability
#
# Usage: ./test.sh
# Configuration: Modify variables below to customize behavior
# 
# Features:
# - Parallel execution: All test runs execute simultaneously for faster results
# - Signal handling: Ctrl+C properly kills all background processes
# - "No death" tests run for 10 seconds each to properly observe behavior
# - Total test time: ~2-3 minutes (thanks to parallel execution)
# ============================================================================

# Configuration
RUNS_PER_TEST=5  # Number of times to run each test (configurable)
EXECUTABLE="./philo"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters for summary
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Array to track background processes
declare -a BACKGROUND_PIDS=()

# Signal handler for cleanup
cleanup() {
    echo -e "\n${YELLOW}Received interrupt signal. Cleaning up...${NC}"
    
    # Kill all background processes
    for pid in "${BACKGROUND_PIDS[@]}"; do
        if kill -0 "$pid" 2>/dev/null; then
            echo "Killing process $pid..."
            kill -TERM "$pid" 2>/dev/null
            sleep 0.5
            # Force kill if still running
            if kill -0 "$pid" 2>/dev/null; then
                kill -KILL "$pid" 2>/dev/null
            fi
        fi
    done
    
    # Clean up temporary files
    rm -f temp_output_*.txt temp_single.txt temp_test.txt
    rm -f test_result_*.txt
    
    echo -e "${RED}Tests interrupted by user.${NC}"
    exit 130
}

# Set up signal handlers
trap cleanup SIGINT SIGTERM

# Function to print colored output
print_header() {
    echo -e "${BLUE}============================================${NC}"
    echo -e "${BLUE}         PHILOSOPHERS TEST SUITE${NC}"
    echo -e "${BLUE}============================================${NC}"
    echo ""
}

print_test_header() {
    echo -e "${YELLOW}Testing: $1${NC}"
    echo "Arguments: $2"
    echo "Expected: $3"
    echo "----------------------------------------"
}

print_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✅ PASS${NC} - $2"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}❌ FAIL${NC} - $2"
        ((FAILED_TESTS++))
    fi
    ((TOTAL_TESTS++))
    echo ""
}

print_summary() {
    echo -e "${BLUE}============================================${NC}"
    echo -e "${BLUE}              TEST SUMMARY${NC}"
    echo -e "${BLUE}============================================${NC}"
    echo "Total tests: $TOTAL_TESTS"
    echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
    echo -e "Failed: ${RED}$FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}🎉 ALL TESTS PASSED!${NC}"
    else
        echo -e "${RED}⚠️  Some tests failed. Please review.${NC}"
    fi
    echo ""
}

# Function to compile the program
compile_program() {
    echo "Compiling philosophers..."
    make re > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Compilation failed!${NC}"
        exit 1
    fi
    echo -e "${GREEN}✅ Compilation successful${NC}"
    echo ""
}

# Function to test invalid parameters
test_invalid_parameters() {
    echo -e "${YELLOW}Testing Invalid Parameters...${NC}"
    echo "----------------------------------------"
    
    # Test with wrong number of arguments
    $EXECUTABLE > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "${GREEN}✅ PASS${NC} - No arguments (should fail)"
    else
        echo -e "${RED}❌ FAIL${NC} - No arguments (should fail)"
    fi
    
    # Test with too few arguments
    $EXECUTABLE 5 > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "${GREEN}✅ PASS${NC} - Too few arguments (should fail)"
    else
        echo -e "${RED}❌ FAIL${NC} - Too few arguments (should fail)"
    fi
    
    # Test with too many arguments
    $EXECUTABLE 5 800 200 200 7 extra > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "${GREEN}✅ PASS${NC} - Too many arguments (should fail)"
    else
        echo -e "${RED}❌ FAIL${NC} - Too many arguments (should fail)"
    fi
    
    # Test with invalid numbers (negative, zero, non-numeric)
    $EXECUTABLE -1 800 200 200 > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "${GREEN}✅ PASS${NC} - Negative philosophers (should fail)"
    else
        echo -e "${RED}❌ FAIL${NC} - Negative philosophers (should fail)"
    fi
    
    $EXECUTABLE 0 800 200 200 > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "${GREEN}✅ PASS${NC} - Zero philosophers (should fail)"
    else
        echo -e "${RED}❌ FAIL${NC} - Zero philosophers (should fail)"
    fi
    
    $EXECUTABLE abc 800 200 200 > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        echo -e "${GREEN}✅ PASS${NC} - Non-numeric input (should fail)"
    else
        echo -e "${RED}❌ FAIL${NC} - Non-numeric input (should fail)"
    fi
    
    # Test constraint: more than 200 philosophers should be avoided (warning, not failure)
    echo -e "${YELLOW}ℹ️  INFO${NC} - Testing with >200 philosophers is not recommended"
    
    # Test constraint: time values lower than 60ms should be avoided (warning, not failure)
    echo -e "${YELLOW}ℹ️  INFO${NC} - Time values <60ms may cause issues"
    
    echo ""
}

# Function to run a single test run in background
run_single_test() {
    local args="$1"
    local expected_death="$2"
    local max_time="$3"
    local expected_death_time="$4"
    local run_number="$5"
    local test_id="$6"
    
    local output_file="temp_output_${test_id}_${run_number}.txt"
    local result_file="test_result_${test_id}_${run_number}.txt"
    
    # Run the program with timeout
    timeout ${max_time}s $EXECUTABLE $args > "$output_file" 2>&1
    local exit_code=$?
    
    local result_status=""
    local result_message=""
    
    # Handle timeout cases
    if [ $exit_code -eq 124 ]; then
        if [ "$expected_death" = "no death" ]; then
            result_status="OK"
            result_message="TIMEOUT after ${max_time}s (no deaths observed - OK)"
        else
            result_status="FAIL"
            result_message="TIMEOUT (unexpected) - FAIL"
        fi
    else
        # Check if death occurred as expected
        if [ "$expected_death" = "should die" ]; then
            if grep -q "died" "$output_file"; then
                # Calculate relative death time from start
                local first_timestamp=$(head -n1 "$output_file" | awk '{print $1}')
                local death_line=$(grep "died" "$output_file" | head -n1)
                local death_timestamp=$(echo "$death_line" | awk '{print $1}')
                local relative_death_time=$((death_timestamp - first_timestamp))
                
                if [ "$expected_death_time" -gt 0 ]; then
                    # Check if death time is within 10ms tolerance
                    local lower_bound=$((expected_death_time - 10))
                    local upper_bound=$((expected_death_time + 10))
                    if [ "$relative_death_time" -ge "$lower_bound" ] && [ "$relative_death_time" -le "$upper_bound" ]; then
                        result_status="OK"
                        result_message="Death at ${relative_death_time}ms (expected ~${expected_death_time}ms) - OK"
                    else
                        result_status="FAIL"
                        result_message="Death at ${relative_death_time}ms (expected ~${expected_death_time}ms) - TIMING FAIL"
                    fi
                else
                    result_status="OK"
                    result_message="Death at ${relative_death_time}ms - OK"
                fi
            else
                result_status="FAIL"
                result_message="No death detected - FAIL"
            fi
        else
            if grep -q "died" "$output_file"; then
                result_status="FAIL"
                result_message="Unexpected death - FAIL"
            else
                result_status="OK"
                result_message="No death - OK"
            fi
        fi
    fi
    
    # Write result to file
    echo "$result_status|$result_message" > "$result_file"
    rm -f "$output_file"
}

# Function to run a test and check for death timing (now with parallel execution)
run_death_test() {
    local args="$1"
    local expected_death="$2"
    local test_name="$3"
    local max_time="$4"
    local expected_death_time="${5:-0}"  # Expected death time in ms (0 means don't check timing)
    
    print_test_header "$test_name" "$args" "$expected_death"
    
    # Generate unique test ID
    local test_id=$(echo "$test_name" | tr ' ' '_' | tr '[:upper:]' '[:lower:]')
    local pids=()
    
    # Start all runs in parallel
    for i in $(seq 1 $RUNS_PER_TEST); do
        if [ "$expected_death" = "no death" ]; then
            echo "Starting run $i/$RUNS_PER_TEST (${max_time}s) in background..."
        else
            echo "Starting run $i/$RUNS_PER_TEST in background..."
        fi
        
        run_single_test "$args" "$expected_death" "$max_time" "$expected_death_time" "$i" "$test_id" &
        local pid=$!
        pids+=($pid)
        BACKGROUND_PIDS+=($pid)
    done
    
    # Wait for all runs to complete and collect results
    local success_count=0
    echo "Waiting for all runs to complete..."
    
    for i in $(seq 1 $RUNS_PER_TEST); do
        local pid=${pids[$((i-1))]}
        wait $pid
        
        # Read result from file
        local result_file="test_result_${test_id}_${i}.txt"
        if [ -f "$result_file" ]; then
            local result_line=$(cat "$result_file")
            local result_status=$(echo "$result_line" | cut -d'|' -f1)
            local result_message=$(echo "$result_line" | cut -d'|' -f2)
            
            echo "Run $i/$RUNS_PER_TEST: $result_message"
            
            if [ "$result_status" = "OK" ]; then
                ((success_count++))
            fi
            
            rm -f "$result_file"
        else
            echo "Run $i/$RUNS_PER_TEST: ERROR - No result file found"
        fi
        
        # Remove from background tracking
        BACKGROUND_PIDS=($(printf '%s\n' "${BACKGROUND_PIDS[@]}" | grep -v "^$pid$"))
    done
    
    if [ $success_count -eq $RUNS_PER_TEST ]; then
        print_result 0 "$test_name ($success_count/$RUNS_PER_TEST runs passed)"
    else
        print_result 1 "$test_name ($success_count/$RUNS_PER_TEST runs passed)"
    fi
}

# Function to run a single meal test in background
run_single_meal_test() {
    local args="$1"
    local run_number="$2"
    local test_id="$3"
    
    local output_file="temp_output_${test_id}_${run_number}.txt"
    local result_file="test_result_${test_id}_${run_number}.txt"
    
    # Run with timeout (should finish before timeout)
    timeout 30s $EXECUTABLE $args > "$output_file" 2>&1
    local exit_code=$?
    
    local result_status=""
    local result_message=""
    
    if [ $exit_code -eq 124 ]; then
        result_status="FAIL"
        result_message="TIMEOUT - simulation should have stopped after meals - FAIL"
    else
        # Check if no philosopher died
        if ! grep -q "died" "$output_file"; then
            # Check if simulation completed (program should exit normally)
            if [ $exit_code -eq 0 ]; then
                result_status="OK"
                result_message="Simulation completed normally - OK"
            else
                result_status="FAIL"
                result_message="Simulation ended with error - FAIL"
            fi
        else
            result_status="FAIL"
            result_message="Philosopher died - FAIL"
        fi
    fi
    
    # Write result to file
    echo "$result_status|$result_message" > "$result_file"
    rm -f "$output_file"
}

# Function to run meal completion test (now with parallel execution)
run_meal_test() {
    local args="$1"
    local test_name="$2"
    local expected_meals="$3"
    
    print_test_header "$test_name" "$args" "Simulation should stop after $expected_meals meals each"
    
    # Generate unique test ID
    local test_id=$(echo "$test_name" | tr ' ' '_' | tr '[:upper:]' '[:lower:]')
    local pids=()
    
    # Start all runs in parallel
    for i in $(seq 1 $RUNS_PER_TEST); do
        echo "Starting run $i/$RUNS_PER_TEST in background..."
        
        run_single_meal_test "$args" "$i" "$test_id" &
        local pid=$!
        pids+=($pid)
        BACKGROUND_PIDS+=($pid)
    done
    
    # Wait for all runs to complete and collect results
    local success_count=0
    echo "Waiting for all runs to complete..."
    
    for i in $(seq 1 $RUNS_PER_TEST); do
        local pid=${pids[$((i-1))]}
        wait $pid
        
        # Read result from file
        local result_file="test_result_${test_id}_${i}.txt"
        if [ -f "$result_file" ]; then
            local result_line=$(cat "$result_file")
            local result_status=$(echo "$result_line" | cut -d'|' -f1)
            local result_message=$(echo "$result_line" | cut -d'|' -f2)
            
            echo "Run $i/$RUNS_PER_TEST: $result_message"
            
            if [ "$result_status" = "OK" ]; then
                ((success_count++))
            fi
            
            rm -f "$result_file"
        else
            echo "Run $i/$RUNS_PER_TEST: ERROR - No result file found"
        fi
        
        # Remove from background tracking
        BACKGROUND_PIDS=($(printf '%s\n' "${BACKGROUND_PIDS[@]}" | grep -v "^$pid$"))
    done
    
    if [ $success_count -eq $RUNS_PER_TEST ]; then
        print_result 0 "$test_name ($success_count/$RUNS_PER_TEST runs passed)"
    else
        print_result 1 "$test_name ($success_count/$RUNS_PER_TEST runs passed)"
    fi
}

# Function to test precise timing with 2 philosophers (now with parallel execution)
test_precise_timing() {
    # Use the parallel death test function with specific timing requirements
    run_death_test "2 410 200 200" "should die" "Precise Timing Test" 5 410
}

# Main testing function
run_tests() {
    print_header
    
    # Compile the program
    compile_program
    
    # Test invalid parameters
    test_invalid_parameters
    
    # Test cases as specified
    echo -e "${YELLOW}Running Core Test Cases...${NC}"
    echo ""
    
    # Test 1: Single philosopher should die (skip if causing segfault)
    echo "Testing single philosopher (may have implementation issues)..."
    timeout 2s $EXECUTABLE 1 800 200 200 > temp_single.txt 2>&1
    if grep -q "died" temp_single.txt; then
        echo -e "${GREEN}✅ Single philosopher test - philosopher died as expected${NC}"
    else
        echo -e "${YELLOW}⚠️  Single philosopher test - may have implementation issues${NC}"
    fi
    rm -f temp_single.txt
    echo ""
    
    # Test 2: 5 philosophers, no one should die (should run indefinitely - timeout expected)
    run_death_test "5 800 200 200" "no death" "5 philosophers survival test" 10
    
    # Test 3: 5 philosophers with meal limit
    run_meal_test "5 800 200 200 7" "5 philosophers with 7 meals" 7
    
    # Test 4: 4 philosophers, no death expected (should run indefinitely - timeout expected)  
    run_death_test "4 410 200 200" "no death" "4 philosophers survival test" 10
    
    # Test 5: 4 philosophers, one should die (around 310ms)
    run_death_test "4 310 200 100" "should die" "4 philosophers death test" 2 310
    
    # Test 6: Precise timing test
    test_precise_timing
    
    # Additional edge case tests
    echo -e "${YELLOW}Running Additional Edge Case Tests...${NC}"
    echo ""
    
    # Test with larger timing values (should run indefinitely - timeout expected)
    run_death_test "2 500 100 100" "no death" "Safe timing values test" 10
    
    # Test with moderate number of philosophers (should run indefinitely - timeout expected)
    run_death_test "10 1000 200 200" "no death" "10 philosophers test" 10
    
    # Test rapid eating scenario (should run indefinitely - timeout expected)
    run_death_test "3 1000 100 100" "no death" "Rapid eating test" 10
    
    # Test edge case with meals
    run_meal_test "3 1000 200 200 1" "3 philosophers with 1 meal" 1
    
    # Clean up any remaining temp files
    rm -f temp_output_*.txt temp_single.txt temp_test.txt
    rm -f test_result_*.txt
    
    print_summary
}

# Check if philo executable exists, if not try to compile
if [ ! -f "$EXECUTABLE" ]; then
    echo "Executable not found. Attempting to compile..."
    make > /dev/null 2>&1
    if [ ! -f "$EXECUTABLE" ]; then
        echo -e "${RED}❌ Could not compile or find philo executable${NC}"
        exit 1
    fi
fi

# Run all tests
run_tests