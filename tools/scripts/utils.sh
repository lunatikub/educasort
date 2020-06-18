# Print an error on stderr with the line and the script name
# $1: line in the caller script
# $2: caller script
# $1: message to dump
err()
{
    local line=$1
    local script_name=$2
    local msg=$3

    echo "${SCRIPT_NAME} error (line:${line}): $msg..." >&2
    exit 1
}

# Log an info message on stdout.
# $1: message to dump
step()
{
    local msg=$1
    local color=$2

    printf "${color[purple]}[step]${color[reset]} $msg\n"
}
