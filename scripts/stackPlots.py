from ROOT import *
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-s", "--sample", dest="sample", default="znunu",
                  help="sample to analyze")
parser.add_option("-f", "--file", dest="file", default="HTvalidation.root",
                  help="input root file")
parser.add_option("-x", dest="x", default="HT",
                  help="independent variable to be plotted")

(options, args) = parser.parse_args()

class plotterInput : 
    
    def __init__(self,
                 lineColor_=1,
                 lineWidth_=2,
                 lineStyle_=1,
                 fillColor_=0,
                 fillStyle_=1,
                 drawOptions_="",
                 histoTag_="",
                 stack_=False,
                 scale_=1.0,
                 norm_=False,
                 legLabel_=""
                 ):
        
        #### MODIFYING THIS SO THAT ARGUMENT NAMES CAN
        #### BE SPECIFIED IN THE CALL TO THE CTOR

        self.legLabel=legLabel_
        self.lineColor=lineColor_
        self.lineWidth=lineWidth_
        self.lineStyle=lineStyle_
        self.fillColor=fillColor_
        self.fillStyle=fillStyle_
        self.drawOptions=drawOptions_
        self.histoTag=histoTag_
        self.stack=stack_
        self.scale=scale_
        self.norm=norm_
        self.histo=None

    def setStyle(self) :
        
        self.histo.SetLineColor(self.lineColor)
        self.histo.SetLineWidth(self.lineWidth)
        self.histo.SetLineStyle(self.lineStyle)
        self.histo.SetFillColor(self.fillColor)
        self.histo.SetFillStyle(self.fillStyle)
        
    def drawHisto(self,options="") :
        if self.histo == None : 
            print "Problem with null histogram"
            return 
        self.histo.Draw("{0},{1}".format(self.drawOptions,options))

def stackPlots( sampleChoices , inputFile , x , log=False):

    f = TFile(inputFile)
    stack = THStack("stack","stack")

    for sample in sampleChoices : 

        print sample.histoTag

        sample.histo = f.Get(x+"_"+sample.histoTag)#+"_"+samples[sample][i]) )
        if sample.histo == None : 
            print "error retrieving ",x+"_"+sample.histoTag# +"_"+samples[sample][i]
            continue
                #assert False

        sample.setStyle()
        sample.histo.SetMinimum(1)
            ### !!!!!!!!!!!!!!!!!!!!
            ### fudge factor for QCD
            ### !!!!!!!!!!!!!!!!!!!!
        if( sample.histoTag == "QCD" ): 
            sample.histo.Scale(1./7.)
        if sample.stack : 
            stack.Add(sample.histo)
            
    stack.Draw("histo")

    leg = TLegend(0.6,0.6,0.9,0.9)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)

    max = 0.
    
    ### superpose non stack plots onto stack plot
    for sample in sampleChoices : 

        if not sample.stack and sample.histo != None :
            print sample.histoTag
            sample.setStyle()
            #sample.histo.SetLineColor(sample.lineColor)
            #sample.histo.SetLineWidth(sample.lineWidth)
            #sample.histo.SetLineStyle(sample.lineStyle)
            #sample.histo.Scale(1/200000.)
            if sample.norm :
                sample.histo.Scale(1/sample.histo.Integral())
            if sample.histo.GetMaximum() > max : 
                max = sample.histo.GetMaximum()
                sampleChoices[0].histo.SetMaximum(max)
            sample.histo.Draw("histo,SAME")

            leg.AddEntry(sample.histo,sample.legLabel,"l")
            
        if sample.stack and sample.histo != None : 
            stack.GetHistogram().GetYaxis().SetTitle(sample.histo.GetYaxis().GetTitle());
            stack.GetHistogram().GetXaxis().SetTitle(sample.histo.GetXaxis().GetTitle());
            
            leg.AddEntry(sample.histo,sample.legLabel,"f")
            
    #stack.SetMaximum(10000000)
    stack.SetMinimum(1)
    
    #leg.Draw()
    can.SaveAs("{0}_compareShapes.png".format(x))
    #can.SetLogy()
    #can.SaveAs("{0}_compareShapes.png".format(x))

if __name__ == "__main__":


    sampleColors = { "znunu" : kBlue+1 ,
                     "ttbar" : kMagenta+1 ,
                     "Wjets" : kCyan+1 , 
                     "QCD" : kGreen+1 }
    
    samples = {"znunu" : ["",
                          #"0_600",
                          #"600_1200",
                          #"1200_2000",
                          #"2000_2900",
                          #"2900_3900",
                          #"3900_5000",
                          #"5000_100000" 
                          ],
               "Wjets" : ["",
                          #"0_400",
                          #"400_900", 	 
                          #"900_1600",    
                          #"1600_2500",   
                          #"2500_3500",   
                          #"3500_4600",   
                          #"4600_5700",   
                          #"5700_10000"
                          ],
               "ttbar" : ["",
                          #"0_600",    	 
                          #"600_1200",  	 
                          #"1200_1900",   
                          #"1900_2700",  
                          #"2700_3600",  
                          #"3600_4600",  
                          #"4600_100000"
                          ], 
               "QCD" : ["",
                        #"0_300",       	 
                        #"300_600",   
                        #"600_1000",   	 
                        #"1000_1600",  	 
                        #"1600_2400",   
                        #"2400_3300",   
                        #"3300_4300",   
                        #"4300_5300",   
                        #"5300_6300",   
                        #"6300_100000"
                        ] }
    
    stackPlots( plotterInput(histoTag_="znunu") , options.file , options.x )
    
