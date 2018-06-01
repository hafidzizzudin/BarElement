import os

# Collecting all cpp
listcpp = [x for x in os.listdir("../src") if x.endswith(".cpp")]

# Openfile
fileinput = open('Makefile', 'w+')

# Write all
fileinput.write("all: BAR")

# Write all objects: dependecies

# Write BAR object
## object and dependencies
count =0
for i in listcpp:
    if count==0:
        fileinput.write(f"\n\nBAR: {i[:-4]}.o ")
        count += 1;
    else:
        fileinput.write(f"{i[:-4]}.o ")
## Compilation instruction
count =0
for i in listcpp:
    if count==0:
        fileinput.write(f"\n\tg++ {i[:-4]}.o ")
        count += 1
    elif count < len(listcpp)-1:
        fileinput.write(f"{i[:-4]}.o ")
        count += 1
    else:
        fileinput.write(f"{i[:-4]}.o -o BAR")

# Write each object
count = 0
for i in listcpp:
    if count == 0:
        fileinput.write(f"\n\n{i[:-4]}.o: ../src/{i}")        
        fileinput.write(f"\n\tg++ -c ../src/{i}\n\n")
        count += 1
    else:
        fileinput.write(f"{i[:-4]}.o: ../src/{i}")        
        fileinput.write(f"\n\tg++ -c ../src/{i}\n\n")

#Write Clean
fileinput.write("clean:\n\trm -rf *.o BAR")
