#!/usr/bin/python
import sys, string, locale
from optparse import OptionParser

tab = "        "
space = " "

class Comm:
    def __init__(self, args):
        if args[0] == '-' and args[1] != '-':
            self.line1 = sys.stdin.read().splitlines()
            self.fileName2 = args[1]
            self.file2 = open(self.fileName2, 'r')
            self.line2 = self.file2.read().splitlines()
        elif args[1] == '-' and args[0] != '-':
            self.fileName1 = args[0]
            self.file1 = open(self.fileName1, 'r')
            self.line1 = self.file1.read().splitlines()
            self.line2 = sys.stdin.read().splitlines()
        elif args[1] == '-' and args[0] == '-':
            parser.error("Undefined behavior! can't have both files refer to standard in\
put")
        else:
            self.fileName1 = args[0]
            self.file1 = open(self.fileName1, 'r')
            self.line1 = self.file1.read().splitlines()
            self.fileName2 = args[1]
            self.file2 = open(self.fileName2, 'r')
            self.line2 = self.file2.read().splitlines()
        self.line3 = []


    def compare(self, sort):
        if sort == True:
            self.line1 = sorted(self.line1, key=locale.strxfrm)
            self.line2 = sorted(self.line2, key=locale.strxfrm)

        x = 0
        while x < len(self.line1) and x < len(self.line2):
            cmp = locale.strcoll(self.line1[x], self.line2[x])
            if cmp == 0:
                self.line3.append(self.line1[x])
                self.line1[x] = space
                self.line2[x] = space
            elif cmp > 0:
                self.line1.insert(x, space)
                self.line3.append(space)
            else:
                self.line2.insert(x, space)
                self.line3.append(space)
            x += 1


        if len(self.line1) > len(self.line3):
            y = len(self.line3)
            while y < len(self.line1):
                self.line3.append(space)
                self.line2.append(space)
                y += 1
        elif len(self.line2) > len(self.line3):
            y = len(self.line3)
            while y < len(self.line2):
                self.line3.append(space)
                self.line1.append(space)
                y += 1


    def printThree(self, l1, l2, l3):
        z = 0
        while z < len(l1):
            print l1[z] + tab +l2[z] + tab + l3[z]
            z += 1

    def printTwo(self, l1,l2):
        z = 0
        while z < len(l1):
            if l1[z] != ' ' or l2[z] != ' ':
                print l1[z] + tab + l2[z]
            z += 1

    def printOne(self, l):
        for e in l:
            if e != ' ':
                print e

    def printResult(self,s1,s2,s3):

        if s1 == False and s2 == False and s3 == False:
            self.printThree(self.line1,self.line2,self.line3)
        elif s1 == True and s2 == False and s3 == False:
            self.printTwo(self.line2,self.line3)
        elif s1 == False and s2 == True and s3 == False:
            self.printTwo(self.line1,self.line3)
        elif s1 == False and s2 == False and s3 == True:
            self.printTwo(self.line1,self.line2)

        elif s1 == True and s2 == True and s3 == False:
            self.printOne(self.line3)
        elif s1 == True and s2 == False and s3 == True:
            self.printOne(self.line2)
        elif s1 == False and s2 == True and s3 == True:
            self.printOne(self.line1)

def main():
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Compare sorted files FILE1 and FILE2 line by line.

With no options, produce three-column output.  Column one contains
lines unique to FILE1, column two contains lines unique to FILE2,
and column three contains lines common to both files."""

    parser = OptionParser(usage=usage_msg, version="%prog 1.0")

    parser.add_option("-1", action="store_true", dest="file_1",default=False,
                      help="suppress column 1 (lines unique to FILE1)")
    parser.add_option("-2", action="store_true", dest="file_2",default=False,
                      help="suppress column 2 (lines unique to FILE2)")
    parser.add_option("-3", action="store_true", dest="file_3",default=False,
                      help="suppress column 2 (lines unique to FILE2)")
    parser.add_option("-u", action="store_true", dest="unsorted",default=False,
                      help="files are unsorted")

    options, args = parser.parse_args(sys.argv[1:])

    needSort = options.unsorted
    if len(args) != 2:
        parser.error("missing files")
    try:
        comm = Comm(args)
        comm.compare(needSort)
        comm.printResult(options.file_1,options.file_2,options.file_3)
    except IOError as err:
        errno = err.errno
        strerror = err.strerror
        parser.error("I/O error({0}): {1}".
                      format(errno, strerror))


if __name__=='__main__':
    main()
