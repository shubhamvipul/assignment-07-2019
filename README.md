# assignment-07-2019

TASK 1

Libraries used:

mutex; chrono; thread; nlohmann/json

Commands to be run:

python3 q.py
g++ -std=c++11

The output of the program is in the console. Kindly note that the id-lists for Query 3 and 4 are present but have note been printed.

--------------

TASK 2

Multithreading has been used for each 1000 rows of json; can be increased to 10,000 for larger files.
Mutex lock has been used for shared global resource (struct that contains the answers). Program only has to go to the mutex-protected resource after processing is done on that chunck of json and variables are ready for comparing or pushing to the list.

--------------

TASK 3

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


Difference between serialized process and multi-threaded one is not much (multi-threaded being the more efficient one), meaning assignment is taking up a significant portion of time.



