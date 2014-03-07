import mytools,shutil
import glob, os, sys
import ROOT

from optparse import OptionParser

# parse command line arguments
parser = OptionParser()
parser.add_option("--idir",dest="idir",default="input",help="path to input directory with root files, default=%default")
parser.add_option("--odir",dest="odir",default="",help="path to output directory with root files, default=IDIR_newErrors")
(options, args) = parser.parse_args()

options.idir = options.idir.rstrip("/")
if len(options.odir)== 0:
    options.odir = options.idir + "_weighted"
sys.argv.append("-b")

# check options
def checkLocationOption(location,title,option):
    if not os.path.exists(location):
        print "ERROR: given {0}, {1}, does not exist.".format(title,location)
        print "       Specify {0} with option {1}.".format(title,option)
        sys.exit()
	
print "INPUT DIR: " + options.idir
_file = glob.glob(options.idir + "/*.root")
file = dict()
for __file in _file:
    _sample = os.path.split(__file)[1].replace(".root","")
    file.update([[_sample,__file]])
    
# create output directory
if os.path.exists(options.odir):
    print "ERROR: ODIR already exists"
    sys.exit()
print "OUTPUT DIR: " + options.odir
os.mkdir(options.odir)    

#find files
for _sample in sorted(file.keys()):
    _file = file[_sample]
    # list file content
    tfile = ROOT.TFile.Open(_file)
    path  = mytools.listRootFile(tfile)
    
    # create output root file
    otfile = ROOT.TFile.Open(options.odir + "/" + _sample + ".root","RECREATE")
    
    for _path in path:
        o = tfile.Get(_path)


        # create directories
        if o.InheritsFrom("TDirectory"):
            otfile.mkdir(_path)
            continue

        # clone, weight and write histograms
        if o.InheritsFrom("TH1"):
            _o = o.Clone()
            for x in range(0, _o.GetNbinsX()):
	    	events = _o.GetBinContent(x+1)
		if(events>0):
			alpha=0.32
			low  = events - ROOT.TMath.ChisquareQuantile(alpha/2,2*events)/2
			high = ROOT.TMath.ChisquareQuantile(1-alpha/2,2*events+2)/2 - events
			if(low-events>high):
				error=low
			else:
				error=high
			_o.SetBinError(x+1,error)
            otfile.cd(os.path.split(_path)[0])
            _o.Write()

    # closing ...
    tfile.Close()
    otfile.Close()        
