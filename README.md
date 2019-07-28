## assignment-07-2019

*Libraries used:*

chrono; thread; nlohmann/json

*Commands to be run:*

python3 q.py
g++ -std=c++11

The input json file is to be named as 'json_text.txt' in the 'data' folder.
The file is supposed to have number of json objects in multiples of -

- 100 if the total number of objects is below 5,000.
- 1,000 if the total number of objects is below 100,000.
- 10,000 if the total number of objects is more than 100,000.

This is because the python script generates files containing chunks of json objects in intervals of the latter number (stored in 'temp.txt' by python-script) above depending on the total number of objects. Each file-read and operation execution takes place in an independent thread, as suggested in the previous meeting. 
To recap, my earlier implementation only performed the operations on the thread after the read operation in the main function which took a significant portion of time. With the current implementation, by reading files in parallel, the speed-up is at least two-fold than on a single thread or the previous implementation. Also, mutex-lock was removed since now the results are stored in independent object variables than in a single object. In the end, a 'reduce' type of operation summarizes the results.

Outputs for the provided three files are stored in the results folder. The results file produced on running the above script and program is stored in the same folder.

sysctl hw.physicalcpu hw.logicalcpu
> 2; 4

Thus, 2 physical cores.

sysctl -n hw.memsize: 
> 17179869184 bytes = 16 GB
sysctl -n hw.physmem: 
> 2147483648 = 2 GB

Thus, size of physical memory is 2GB.

diskutil info disk0
>  Solid State:               Yes

SSD hard-disk is present.

system_profiler SPSoftwareDataType
> System Software Overview:

      System Version: macOS 10.14.5 (18F132)
      Kernel Version: Darwin 18.6.0
      Boot Volume: Macintosh HD
      Boot Mode: Normal
      Computer Name: Shubham’s MacBook Pro
      User Name: Shubham Vipul Majmudar (shubham)
      Secure Virtual Memory: Enabled
      System Integrity Protection: Enabled
      Time since boot: 6 days 17:32

macOS 10.14.5




