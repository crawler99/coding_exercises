#!/usr/bin/env python
import sys
import subprocess
import time
from datetime import date, timedelta
import datetime
import re
import sys
import os
import string
from datetime import datetime
import time
from optparse import OptionParser
import socket
import pwd, grp
import smtplib
INPUTFILE = ""
INTERVAL = 0
THRESHOLD = 0
SLEEPTIME = 0
SUBSCRIPLIST=['gwei@liquidcapital.com','ylei@liquidcapital.com']
"""read a file returning the lines in reverse order for each call of readline()
This actually just reads blocks (4096 bytes by default) of data from the end of
the file and returns last line in an internal buffer.  I believe all the corner
cases are handled, but never can be sure..."""

def parseCmd():
	"""handles command line options"""	
	usage = "usage: %prog -t --threshold [disk usage threshold in percent], -s --sleep [monitor interval in seconds]"
	parser = OptionParser(usage=usage,version="%prog 1.0")
	parser.add_option("-t", "--threshold", dest="threshold", help="disk usage threshhold in percent(e.g: 95 means 95%)")
	parser.add_option("-s", "--sleep", dest="sleepTime", help="monitor interval in seconds")
	global THRESHOLD
	global SLEEPTIME
	(options, args) = parser.parse_args()
	athreshold = options.threshold
	sleepInter = options.sleepTime
	if athreshold is None:
		print "please specify the monitor athreshold as seconds"
		parser.print_help()
		sys.exit()
	if athreshold and not athreshold.isdigit():
		print "please specify the monitor athreshold as seconds"
		sys.exit()
	if sleepInter and not sleepInter.isdigit():
		print "please specify the sleep athreshold as seconds"
		sys.exit()
	SLEEPTIME = sleepInter	
	THRESHOLD = int(athreshold)

def sendMailToSubscribers(messageString, mailList):
	hostname = socket.gethostname()
	SERVER = "192.168.29.67"

	FROM = hostname
	#TO = ["gwei@liquidcapital.com"] # must be a list
	TO = mailList
	if len(TO) <= 0:
		return
	SUBJECT = "Disk usage is high on host: {0}".format(hostname)

	TEXT = messageString
	# Prepare actual message
	message = """From: %s\nTo: %s\nSubject: %s\n%s""" % (FROM, ", ".join(TO), SUBJECT, TEXT)

	# Send the mail
	try:
		server = smtplib.SMTP(SERVER)
		server.sendmail(FROM, TO, message)
		server.quit()
		print "Successfully sent mail"
	except smtplib.SMTPException:
		print "Error: unable to send email"
def getDiskUsage():
	MONITORPAR = "/dev/sda3"
        special_dir = ["/opt/developer","/var/reactor"]
	totalsize = 0
	userPercent = 0
	iRet = False
	usageRegex = r"(.*?)\s+(.*?)G\s+(.*?)\s+(.*?)\s+(\d+)%"
	lowUsageRegex = r"\d+K"
	cmdRe = subprocess.Popen(["df", "-h", MONITORPAR], stdout=subprocess.PIPE)
	output = cmdRe.communicate()[0]
	output = output.split('\n')[1]
	regexObj = re.search(usageRegex, output, re.IGNORECASE)
	if regexObj:
		totalsize = regexObj.group(2)
		userPercent = regexObj.group(5)
	print "total size is %sG, used is %s%%" % (totalsize,userPercent)

	users = subprocess.Popen(["ls", "/home"], stdout=subprocess.PIPE)
	output = users.communicate()[0]
	output = output.split('\n')
	monitorUsers = []
	usedPerUser = 0
	mailMessage = "Usage details of each user:\n"
	usersToNotice = []
	for item in output:
		if item:
			homedir = "/home/"+item
			cmdResult = subprocess.Popen(["df", "-T", homedir], stdout=subprocess.PIPE)
			mountPar = cmdResult.communicate()[0]
			mountPar = mountPar.split('\n')[1].split(" ")[0]
			if mountPar == "/dev/sda3":
				print "user: %s, mount on: %s" %(item,mountPar)
				cmdResult = subprocess.Popen(["du", "-hs", homedir], stdout=subprocess.PIPE)
				usage = cmdResult.communicate()[0].split('\n')[0]
				usageNumber = usage.split('\t')[0]
				if re.search(lowUsageRegex, usageNumber,re.IGNORECASE):
					print "bypass the %s" % usage
					continue
				mailMessage += usage
				mailMessage += '\n'
				if item == 'qa':
					item = "qa-china"
				usersToNotice.append(item+'@liquidcapital.com')
	usageRegex_2 = r"(.*?)G\s+(.*?)"
        tmpMessage = ""
	for dir in special_dir:
		tmpcmdRe = subprocess.Popen(["du", "-hs", dir], stdout=subprocess.PIPE)
		output = tmpcmdRe.communicate()[0]
		output = output.split('\n')[0]
		regexObj = re.search(usageRegex_2, output, re.IGNORECASE)
		if regexObj:
			tmpMessage += output
			#print "dir %s used: %s" % (dir, regexObj.group(1))
	if tmpMessage:
		mailMessage += tmpMessage
		mailMessage += '\n'
	#print "I got message %s" % mailMessage
		
	
	if int(userPercent) >= int(THRESHOLD):
		print "Alarm: diskusage %s exceed threshold %s, trying to notice the users: %s" % (userPercent, THRESHOLD, usersToNotice)
		sendMailToSubscribers(mailMessage, usersToNotice)
		iRet = True
	else:
		print "debug: "
	return iRet
		
			
def main():
	parseCmd()
	counter = 0
        moreSleep = 3600
	while True:
		if getDiskUsage():
        		moreSleep += 3600
			time.sleep(int(moreSleep))
			continue
		time.sleep(int(SLEEPTIME))

main()
