with open('input.txt') as f:
    data = f.readlines()

safe_reports = 0
unsafe_reports = []

for report in data:
    safe = True

    levels = [int(level) for level in report.split()]
    increasing = levels[0] < levels[1]
    for i in range(len(levels) - 1):
        if increasing:
            if (levels[i + 1] - levels[i]) not in [1, 2, 3]:
                safe = False
                unsafe_reports.append(levels)
                break
        else:
            if (levels[i] - levels[i + 1]) not in [1, 2, 3]:
                safe = False
                unsafe_reports.append(levels)
                break
    
    if safe:
        safe_reports += 1

dampened_safe_reports = 0

for unsafe_report in unsafe_reports:
    dampened_safe = False

    for i in range(len(unsafe_report)):
        if i < len(unsafe_report) - 1:
            dampened_report = unsafe_report[:i] + unsafe_report[i + 1:]
        else:
            dampened_report = unsafe_report[:i]
        
        safe = True

        increasing = dampened_report[0] < dampened_report[1]
        for i in range(len(dampened_report) - 1):
            if increasing:
                if (dampened_report[i + 1] - dampened_report[i]) not in [1, 2, 3]:
                    safe = False
                    break
            else:
                if (dampened_report[i] - dampened_report[i + 1]) not in [1, 2, 3]:
                    safe = False
                    break
        
        if safe:
            dampened_safe = True
            break

    if dampened_safe:
        dampened_safe_reports += 1 #1 3 2 4 5

print(safe_reports, safe_reports + dampened_safe_reports)
