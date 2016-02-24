from ROOT import *
gROOT.SetBatch(True)
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-s", "--sample", dest="sample", default="znunu",
                  help="sample to analyze")
parser.add_option("-f", "--file", dest="file", default="HTvalidation.root",
                  help="input root file")
parser.add_option("-x", dest="x", default="HT",
                  help="independent variable to be plotted")

(options, args) = parser.parse_args()

sampleColors = { "znunu" : kBlue+1 ,
                 "ttbar" : kMagenta+1 ,
                 "Wjets" : kCyan+1 , 
                 "QCD" : kGreen+1 }

samples = {"znunu" : ["0_600",
                      "600_1200",
                      "1200_2000",
                      "2000_2900",
                      "2900_3900",
                      "3900_5000",
                      "5000_100000" ],
           "Wjets" : [#"0_400",
                      "400_900", 	 
                      "900_1600",    
                      "1600_2500",   
                      "2500_3500",   
                      "3500_4600",   
                      "4600_5700",   
                      "5700_10000"
                      ],
           "ttbar" : ["0_600",    	 
                      "600_1200",  	 
                      "1200_1900",   
                      "1900_2700",  
                      "2700_3600",  
                      "3600_4600",  
                      "4600_100000"], 
           "QCD" : [#"0_300",       	 
                    "300_600",   
                    "600_1000",   	 
                    "1000_1600",  	 
                    "1600_2400",   
                    "2400_3300",   
                    "3300_4300",   
                    "4300_5300",   
                    "5300_6300",   
                    "6300_100000"] }

def stackPlots( sampleChoice , inputFile , x ):

    #print "sampleChoice:",sampleChoice
    #print "inputFile:",inputFile
    #print "x:",x
    #print "sampleChoice in samples:",(sampleChoice in samples)
    #print "sampleChoice==all:",(sampleChoice==all)

    assert ( sampleChoice in samples or sampleChoice == "all" )
    f = TFile(inputFile)

    stack = THStack("stack","stack")
    histos = [] 
    
    sampleList = []
    if sampleChoice == "all" : 
        sampleList = samples.keys()
    else : 
        sampleList = [sampleChoice]

    for sample in sampleList : 
        for i in range( len(samples[sample]) ) :

            histos.append( f.Get(x+"_"+sample+"_"+samples[sample][i]) )
            if histos[-1] == None : 
                print "error retrieving ",x+"_"+sample+"_"+samples[sample][i]
                continue
                #assert False
            if i < len(samples[sample])  :
                histos[-1].SetLineColor(sampleColors[sample])
            else :
                histos[-1].SetLineColor(1)
            histos[-1].SetFillColor(sampleColors[sample])
            histos[-1].SetLineWidth(2)
            histos[-1].SetFillStyle(2)
            #histos[-1].SetMaximum(10000000)
            histos[-1].SetMinimum(1)
            yields = f.Get("baseline4JetYields_"+sample+"_"+samples[sample][i])
            print yields.GetBinContent(0)
            ### this line is now done when the weights are computed
            #histos[-1].Scale(1./yields.GetBinContent(0))
            stack.Add(histos[-1])

    can = TCanvas("can","can",500,500)
    stack.Draw("histo")
    #stack.SetMaximum(10000000)
    stack.SetMinimum(1)

    if sampleChoice == "all" :
        can.SaveAs("{0}_allStack_4jets.png".format(x))
        can.SetLogy()
        can.SaveAs("{0}_allStackLogY_4jets.png".format(x))
    else :
        can.SaveAs("{0}_{1}Stack_4jets.png".format(x,sample))
        can.SetLogy()
        can.SaveAs("{0}_{1}StackLogY_4jets.png".format(x,sample))

if __name__ == "__main__":
    stackPlots( options.sample , options.file , options.x )
