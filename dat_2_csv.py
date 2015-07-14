""" # SystemC AMS DAT To CSV converter
    #
    # Version 1.0
    #
    # Author : Muhammad Haziq bin Kamarul Azman @ KaiserHaz
    #
    # Converts SystemC AMS simulation data to SignalConstructor-viewable CSV format
    # P.S. This is all because of locales!
"""

###
# Imports
###

import sys                    # exit
import getopt                 # getopt
import os                     # open
import string                 # Strings
import re                     # Regexes

def main(argv):
    
   inputfile = ''
   outputfile = ''
   filepath = ''
   
   try:
      opts, args = getopt.getopt(argv,"hi:",["ifile="])
   except getopt.GetoptError:
      print('Usage: test.py [-i <inputfile>|--ifile <inputfile>')
      sys.exit(2)
      
   for opt, arg in opts:
      if opt == '-h':
         print('Conversion SystemC AMS simulation data to SignalConstructor-viewable CSV format')
         print('Usage: test.py [-i <inputfile>|--ifile <inputfile>')
         sys.exit()
      elif opt in ("-i", "--ifile"):
         filepath = arg

   if filepath == '':
      print('Usage: test.py [-i <inputfile>|--ifile <inputfile>')
      sys.exit(1)

   filepath = os.path.join(os.path.dirname(__file__), filepath)

   out = []
   put = '1'
         
   with open(filepath,'r') as fp:
       while put != '':
           put = fp.readline()
           out.append(put)

   fp.close()

   #print(out)
   #print(out[0])

   if os.path.isfile(filepath+".csv"):
       os.remove(filepath+".csv")
       
   fd = open(filepath+".csv", "a")

   i = 0
   put2 = ''
   put3 = ''
   
   put = out[i]
   put = put.lstrip('%')

   for put2 in put.split():
       put3 += '\''+put2+'\''+','

   put3 = put3.rstrip(',')

   #print(put3)

   fd.write(put3+"\n")

   while put != '':
       i += 1
       put3 = ''
   
       put = out[i]
       
       for put2 in put.split():
           put2 = put2.replace(',','.')
           put3 += put2+','

       put3 = put3.rstrip(',')

       #print(put3)

       fd.write(put3+"\n")

   fd.close()

if __name__ == "__main__":
   main(sys.argv[1:])
