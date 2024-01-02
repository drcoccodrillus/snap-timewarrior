#!/Users/alatar/Projects/timew/venv/bin/python3

import datetime
import sys

from timewreport.parser import TimeWarriorParser

parser = TimeWarriorParser(sys.stdin)

total_budget = datetime.timedelta(hours=40)
total_time = datetime.timedelta()

for interval in parser.get_intervals():
    tracked = interval.get_duration()
    # Add some filtering here if needed...
    total_time += tracked

budget_diff = total_budget - total_time

# Print out time budget message
print("{}s of {}s to go...".format(budget_diff.total_seconds(), total_budget.total_seconds()))
