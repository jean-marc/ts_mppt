#extract entries and add time stamp
BEGIN{
	#format similar to regular log files and can be parsed by gnuplot
	printf strftime("%b %d %H:%M:%S")
}
	{
		printf ","$2
	}
END{
	printf "\n"
}

