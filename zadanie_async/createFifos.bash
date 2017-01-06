rm -rf fifos
mkdir fifos
cd fifos
mkfifo $(seq $1)
