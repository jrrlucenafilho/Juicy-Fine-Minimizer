# Define an array with all instance paths
$instance_names = @(
    ".\instances\ex_instance.txt",
    ".\instances\n60A.txt"
    ".\instances\n60B.txt",
    ".\instances\n60C.txt"
    ".\instances\n60D.txt",
    ".\instances\n60E.txt",
    ".\instances\n60F.txt",
    ".\instances\n60G.txt",
    ".\instances\n60H.txt",
    ".\instances\n60I.txt",
    ".\instances\n60J.txt",
    ".\instances\n60K.txt",
    ".\instances\n60L.txt"
)

# Define the CSV file path
$csvFilePath = ".\benchmark.csv"

# Write the header to the CSV file
$header = "instance;optimal_cost;best_cost_found;MH_avg_cost;MH_avg_time;MH_GAP;RVND_avg_cost;RVND_avg_time;RVND_GAP;constr_heur_avg_cost;constr_heur_avg_time;constr_heur_GAP"
Set-Content -Path $csvFilePath -Value $header

# Function to extract value from the results string
function Extract-Value {
    param (
        [string]$results,
        [string]$pattern
    )
    if ($results -match $pattern) {
        return $matches[1]
    }
    return ""
}

# Execute main.exe with each value as an argument
foreach ($instance in $instance_names) {
    # Announce which instance it's running
    Write-Host "Running instance: $instance"

    # Initialize variables
    $optimal_cost = "N/A"
    $best_cost_found = "N/A"
    $MH_avg_cost = "N/A"
    $MH_avg_time = "N/A"
    $MH_GAP = "N/A"
    $RVND_avg_cost = "N/A"
    $RVND_avg_time = "N/A"
    $RVND_GAP = "N/A"
    $constr_heur_avg_cost = "N/A"
    $constr_heur_avg_time = "N/A"
    $constr_heur_GAP = "N/A"

    # Start the process and wait for it to complete
    $outputFile = [System.IO.Path]::GetTempFileName()
    Start-Process -FilePath .\main.exe -ArgumentList $instance -NoNewWindow -Wait -RedirectStandardOutput $outputFile

    # Capture the output of main.exe
    $output = Get-Content $outputFile -Raw

    # Find the index of the "Results" line
    $resultsIndex = $output.IndexOf("==================================Results====================================")

    if ($resultsIndex -ge 0) {
        # Adjust the index to start after the "Results" line
        $resultsIndex += "==================================Results====================================".Length

        # Extract the results part
        $results = $output.Substring($resultsIndex).Trim()

        # Extract values using regex patterns
        $inst_name = Extract-Value -results $results -pattern "Instance:\s*(\S+)"
        $optimal_cost = Extract-Value -results $results -pattern "Optimal Cost:\s*(\d+)"
        $best_cost_found = Extract-Value -results $results -pattern "Best Solution Cost:\s*(\d+)"
        $MH_avg_cost = Extract-Value -results $results -pattern "Metaheuristic Avg Cost:\s*([\d\.eE\+\-]+)"
        $MH_avg_time = (Extract-Value -results $results -pattern "Metaheuristic Avg Time:\s*([\d\.eE\+\-]+)") + " s"
        $MH_GAP = (Extract-Value -results $results -pattern "Metaheuristic GAP:\s*([\d\.\-]+)") + " %"
        $RVND_avg_cost = Extract-Value -results $results -pattern "RVND Avg Cost:\s*([\d\.eE\+\-]+)"
        $RVND_avg_time = (Extract-Value -results $results -pattern "RVND Avg Time:\s*([\d\.eE\+\-]+)") + " s"
        $RVND_GAP = (Extract-Value -results $results -pattern "RVND GAP:\s*([\d\.\-]+)") + " %"
        $constr_heur_avg_cost = Extract-Value -results $results -pattern "Constructive Heuristic Avg Cost:\s*([\d\.eE\+\-]+)"
        $constr_heur_avg_time = (Extract-Value -results $results -pattern "Constructive Heuristic Avg Time:\s*([\d\.eE\+\-]+)") + " s"
        $constr_heur_GAP = (Extract-Value -results $results -pattern "Constructive Heuristic GAP:\s*([\d\.\-]+)") + " %"

        # Create a CSV line
        $csvLine = "$inst_name;$optimal_cost;$best_cost_found;$MH_avg_cost;$MH_avg_time;$MH_GAP;$RVND_avg_cost;$RVND_avg_time;$RVND_GAP;$constr_heur_avg_cost;$constr_heur_avg_time;$constr_heur_GAP"

        # Append the CSV line to the file
        Add-Content -Path $csvFilePath -Value $csvLine

        # Print the results
        Write-Output "Instance $inst_name finished!`n"
    } else {
        Write-Host "Results section not found in the output for $instance"
    }

    # Clean up the temporary file
    Remove-Item $outputFile
}