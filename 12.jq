# P1 Run as: cat <file> | jq -f 12.jq
[recurse | select(type == "number")] | add