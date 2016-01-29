import os

from optparse import OptionParser

parser = OptionParser()
parser.add_option("-s", "--sample", dest="sample", default="znunu_0_600",
                  help="sample to analyze")

(options, args) = parser.parse_args()

jdlFile = """universe = vanilla
Executable = worker.sh
Requirements = OpSys == "LINUX" && (Arch != "DUMMY" )
request_disk = 10000000
request_memory = 10000
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT_OR_EVICT
Transfer_Input_Files = worker.sh
PeriodicRemove = ( JobStatus == 2 ) && ( ( CurrentTime - EnteredCurrentStatus ) > 2400 )
Output = HTvalidation_{0}.stdout
Error = HTvalidation_{0}.stderr
Log = HTvalidation_{0}.condor
notification = Error
notify_user = awhitbe1@FNAL.GOV
x509userproxy = $ENV(X509_USER_PROXY)
Arguments = {0}
Queue 1""".format(options.sample)

outputFile = open("HTvalidation_{0}.jdl".format(options.sample),'w')
outputFile.write(jdlFile)
outputFile.close()

os.system("condor_submit HTvalidation_{0}.jdl".format(options.sample))

