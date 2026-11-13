#!/usr/bin/env bash
# ==============================================================================
# Script: run_all.sh
# Purpose: Compiles, runs, and verifies all 55 C++ DAA laboratory experiments
# ==============================================================================

set -e

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$REPO_ROOT"

echo "=============================================================================="
echo "  IC-709 B: Design & Analysis of Algorithms Laboratory - Automated Test Suite  "
echo "=============================================================================="

TOTAL=0
PASSED=0
FAILED=0

UNITS=(
    "Unit01-Introduction-Algorithms"
    "Unit02-Divide-and-Conquer"
    "Unit03-Greedy-Method"
    "Unit04-Dynamic-Programming"
    "Unit05-Traversal-and-Search"
    "Unit06-Backtracking"
    "Unit07-NP-Hard-NP-Complete"
)

for unit in "${UNITS[@]}"; do
    echo ""
    echo ">>> Running Unit: $unit"
    echo "------------------------------------------------------------------------------"
    
    for exp_dir in "$unit"/*/; do
        if [ -d "$exp_dir" ] && [ -f "${exp_dir}main.cpp" ]; then
            TOTAL=$((TOTAL + 1))
            exp_name="$(basename "$exp_dir")"
            printf "  [%02d/55] %-50s" "$TOTAL" "$exp_name"
            
            # Compile
            if g++ -std=c++17 -O2 "${exp_dir}main.cpp" -o "${exp_dir}main" > /dev/null 2>&1; then
                # Run
                if (cd "$exp_dir" && ./main > run.log 2>&1); then
                    echo " [ PASS ]"
                    PASSED=$((PASSED + 1))
                else
                    echo " [ RUN FAIL ]"
                    FAILED=$((FAILED + 1))
                fi
                rm -f "${exp_dir}main"
            else
                echo " [ COMPILE FAIL ]"
                FAILED=$((FAILED + 1))
            fi
        fi
    done
done

echo ""
echo "=============================================================================="
echo "  Test Summary: Total: $TOTAL | Passed: $PASSED | Failed: $FAILED"
echo "=============================================================================="

if [ "$FAILED" -eq 0 ]; then
    echo ">>> ALL 55 EXPERIMENTS COMPILED AND PASSED VERIFICATION SUCCESSFULLY! <<<"
    exit 0
else
    echo ">>> SOME EXPERIMENTS FAILED VERIFICATION. <<<"
    exit 1
fi
