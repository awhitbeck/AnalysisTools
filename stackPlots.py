from ROOT import *
gROOT.SetBatch(True)
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-s", "--sample", dest="sample", default="znunu",
                  help="sample to analyze")
parser.add_option("-f", "--file", dest="file", default="HTvalidation.root",
                  help="input root file")

(options, args) = parser.parse_args()

f = TFile(options.file)
samples = {"znunu" : ["0_600",
                      "600_1200",
                      "1200_2000",
                      "2000_2900",
                      "2900_3900",
                      "3900_5000",
                      "5000_100000" ],
           "Wjets" : ["0_400",
                      "400_900", 	 
                      "900_1600",    
                      "1600_2500",   
                      "2500_3500",   
                      "3500_4600",   
                      "4600_5700",   
                      "5700_10000"],
           "ttbar" : ["0_600",    	 
                      "600_1200",  	 
                      "1200_1900",   
                      "1900_2700",  
                      "2700_3600",  
                      "3600_4600",  
                      "4600_100000"], 
           "QCD" : ["0_300",       	 
                    "300_600",   
                    "600_1000",   	 
                    "1000_1600",  	 
                    "1600_2400",   
                    "2400_3300",   
                    "3300_4300",   
                    "4300_5300",   
                    "5300_6300",   
                    "6300_100000"]}   

assert options.sample in samples

stack = THStack("stack","stack")
histos = [] 

for i in range( len(samples[options.sample]) ) :

    print "i",i
    histos.append( f.Get("HT_"+options.sample+"_"+samples[options.sample][i]) )
    histos[i].SetFillColor(i+1)
    histos[i].SetLineColor(1)
    histos[i].SetLineWidth(2)
    histos[i].SetFillStyle(2)
    histos[i].SetMaximum(10000000)
    histos[i].SetMinimum(1)

    stack.Add(histos[i])

can = TCanvas("can","can",500,500)
stack.Draw("histo")
stack.SetMaximum(10000000)
stack.SetMinimum(1)

can.SetLogy()
can.SaveAs("{0}Stack.png".format(options.sample))

