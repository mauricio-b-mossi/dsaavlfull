# Get all files in the current directory
$files = Get-ChildItem -File

# Initialize an empty array to store the content of each file
$contents = @()

# Loop through each file and add its content to the $contents array
foreach ($file in $files)
{
    if($file.Name -ne "join.ps1")
    {
        $contents += Get-Content $file.FullName
        $contents += "`n"  # Add a newline after each file's content
    }
}

# Join the contents of all files into a single string with preserved formatting
$joinedContent = $contents -join "`n"

# Write the concatenated content to the join.txt file
$joinedContent | Set-Content -Path "join.txt"
