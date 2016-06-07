import os
import sys
import subprocess
import filecmp

# Removes all the files in a given directory path
def deleteDir(path):
    for root, dirs, files in os.walk(path, topdown=False):
        for name in files:
            os.remove(os.path.join(root, name))
        for name in dirs:
            os.rmdir(os.path.join(root, name))
    os.rmdir(path)
    return 0


# # # Beginning of main file # # #

mutants_dir = 'mutants'    # Directory of mutants files
default_domion = 'dominion.c' # Filename of good dominon game
dominion_default_log = 'dominion-default-log.out'
output_dir = 'mutant_output' # Directory for outputs
bin = 'bin'


# Checking for mutants directory
if(os.path.exists(mutants_dir) == 0):
    print("ERROR: Mutants not found. \n")


# Creats a output directory if one does not exisits
# Deletes and creats a new directory for out put if one exisits
if(os.path.exists(output_dir) == 0):
    os.makedirs(output_dir)
elif(os.path.exists(output_dir)):
    deleteDir(output_dir)
    os.makedirs(output_dir)

if(os.path.exists(bin) == 0):
    os.makedirs(bin)
elif(os.path.exists(bin)):
    deleteDir(bin)
    os.makedirs(bin)



# Clean the directory
subprocess.call(["make","clean"])

# Compile good Unittest 1
log = open(output_dir + '/' + dominion_default_log, 'w+')
subprocess.call(["make","unittest1"])
subprocess.call(["make","unittest2"])
subprocess.call(["make","unittest3"])
subprocess.call(["make","unittest4"])
subprocess.call(['./unittest1'], stdout=log)
subprocess.call(['./unittest2'], stdout=log)
subprocess.call(['./unittest3'], stdout=log)
subprocess.call(['./unittest4'], stdout=log)
log.close()

# Run Mutants

i = 0
for path, dirs, files in os.walk(mutants_dir, topdown=False):
    for file in files:
        if (file != "rngs.h" and file != 'rngs.c' and file != 'dominion_helpers.h' and file != 'dominion.h'):
            subprocess.call(['rm', 'dominion.o'])
            # get path of mutant
            file_path =  path + '/' + file

            # Creating log for mutant
            mutant_name = file.split('_')[0]
            mutant_log = mutant_name + '-log.out'
            log = open(output_dir + '/' + mutant_log, "w+")

            # Compiling dominion with mutant
            os.rename(file_path, "mutants/dominion.c")

            cmd = ["gcc", "-c", "mutants/dominion.c", "-g", "dominion.h", "rngs.o", "-Wall", "-fpic", "-coverage", "-lm"]
            subprocess.call(cmd)

            os.rename('mutants/dominion.c', file_path)

            subprocess.call(["make","unittest1"])
            subprocess.call(['./unittest1'], stdout=log)
            subprocess.call(["make", "unittest2"])
            subprocess.call(['./unittest2'], stdout=log)
            subprocess.call(["make", "unittest3"])
            subprocess.call(['./unittest3'], stdout=log)
            subprocess.call(["make", "unittest4"])
            subprocess.call(['./unittest4'], stdout=log)

            # Clean Up
            subprocess.call(['rm', 'unittest1'])
            subprocess.call(['rm', 'unittest2'])
            subprocess.call(['rm', 'unittest3'])
            subprocess.call(['rm', 'unittest4'])

            # for running on mac
            subprocess.call(['rm', 'dominion.gcda'])
            subprocess.call(['rm', 'unittest1.gcda'])
            subprocess.call(['rm', 'unittest2.gcda'])
            subprocess.call(['rm', 'unittest3.gcda'])
            subprocess.call(['rm', 'unittest4.gcda'])

            log.close()



total_mutants = 0
pass_mutants = 0
failed_mutats = 0
for path, dirs, files in os.walk(output_dir):
    for file in files:
        total_mutants += 1
        if(filecmp.cmp(output_dir + '/' + file, output_dir + '/' + dominion_default_log )):
            pass_mutants += 1
        else:
            failed_mutats += 1


log = open("mutantion.txt", "w+")
log.write("Mutation Testing Results\n")
log.write("Total Mutations: %d\n" % total_mutants)
log.write("Passed Mutations: %d\n" % pass_mutants)
log.write("Failed Mutations: %d\n" % failed_mutats)
log.close()












