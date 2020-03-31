# --input-range (-i)
# --head-count(-n)
#--repeat(-r)
#--help

import random, sys, string, argparse
from optparse import OptionParser


class randline:
    def __init__(self, range, record, filename, readed, count):
        #constructor
        if range:
            #print(self.lines+"####")
            if filename == "none":
            #print(self.lines+"####")
              self.lines = record
            else:
              sys.stdout.write("too many operands!")
              return
        elif filename=="-" or filename=="none":
          self.lines = readed
          if len(readed) <= 0:
            return
        
        else:
          file = open(filename, 'r')
          self.lines = file.readlines()
          file.close()

    def normal_shuf(self):
        #temp = random.sample(self.lines, 1)
        temp = random.choice(self.lines)
        self.lines.remove(temp)
        return temp

    def repeat_shuf(self):
        temp= random.sample(self.lines, 1)
        return temp


def main():    #main function
  version_msg = "%prog 2.0"
  usage_msg = """%prog [OPTION]... FILE
      
Output randomly selected lines from FILE."""
  parser = OptionParser(version=version_msg, usage=usage_msg)
  parser.add_option("-n", "--head-count", action="store",
                    dest="count", default=sys.maxsize,
                    help="output at most COUNT lines")
  parser.add_option("-i", "--input-range", action="store",
                    dest="range", default="",
                    help="treat each number LO through HI as an input line")
  parser.add_option("-r", "--repeat", action="store_true",
                    dest="repeat", default="False",
                    help="output lines can be repeated")
  options, args = parser.parse_args(sys.argv[1:])

  
  #Error handling:
  ##error handling for -n(--head-count)
  if options.count:
      try:
          count = int(options.count)
      except:
          parser.error("head counts invalid: {0}"
                       .format(options.count))
      if count < 0:
          parser.error("negative count")

      
  #error handling for -i (--input-range)
  record = []
  if options.range:
      #print("*****")
      try:
          left, right = options.range.split("-")
          left = int(left)
          right = int(right)
      except:
          parser.error("invalid range: {0}"
                       .format(options.range))
      if left > right:
          parser.error("left cannot be bigger than right")
      record.extend(range(left, right+1))
#print(record)

  #error handling for -r (--repeat)
#print("%%%%")
#print(option.repeat)
  if options.repeat == True:
      #print("%%%")
      if len(args)!=0:
          parser.error("too many operands~~" + str(args))


  ##error handing for input files
  linenum = 0
  readed = []
  try:
      filename = args[0]
  except:
      filename = "none"
  if filename == "-":
      filename = "none"
  if filename!="none" and options.range:
      parser.error("too many operands...")

  
  linenum = 0
  readed = []
  #now we can try to count
  if options.range:
      linenum = len(record)
#print(record)
  elif filename=="-" or filename=="none":
      readed = sys.stdin.readlines()
      linenum = len(readed)
  #if options.range:
      #linenum = len(record)
  else:
      file = open(filename, 'r')
      for i in file:
        linenum += 1
      file.close()

      #if linenum > count:
#linenum = count

  #generation of random lines
  try:
      gen = randline(options.range, record, filename, readed, count)
      for j in range(linenum):
          if options.repeat == True:
              #print("****")
                #k=1
                #for k in range(count):
            break
            tmp = gen.repeat_shuf()
            sys.stdout.write(str(tmp))
            sys.stdout.write("\n")
          #k+=1
          #else:
          #  if options.count:
          #    print ("***")
          #    with open(filename) as f:
          #      l = list(f)#line.rstrp() for l in f #list(f)
          #    for c in range(count):
          #      print(random.choice(l))
          #c+=1
                #c = 1
                #idx = random.sample(range(int(linenum)), count)
                #print([linecache.getline(filename, m) for i in idx])
            #t=gen.normal_shuf()
            #sys.stdout.write(str(t))
            #sys.stdout.write("\n")
            #c+=1
          else:
            if options.count:
                break;
                  
            tmp = gen.normal_shuf()
            sys.stdout.write(str(tmp))
            sys.stdout.write("\n")
      if options.repeat == True:
          k=1
          for k in range(count):
            sys.stdout.write(str(random.randint(left, right)))
            sys.stdout.write("\n")
      elif options.count:
          ls=[]
          with open(filename) as f:
              l = list(f)
          for c in range(count):
              #print (str(random.choice(l)), end="")
              tp = random.choice(l)
              l.remove(tp)
              print (tp, end="")
#ls.append(random.sample(l, 1))
#for i in ls:
#print(i)
          
#sys.stdout.write("")
#print("\n")
  except IOError as errno:
      parser.error("I/O error({0}): {1}".
                   format(errno, stderror))

if __name__ == "__main__":
  main()





