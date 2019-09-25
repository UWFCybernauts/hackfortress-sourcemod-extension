## Hackfortress Sourcemod Extension
This component of the UWF Cyber Security Clubs hackfortress competition implementation allows 
for exchanging data with the [hackfortress-exchanger](https://github.com/UWFCybernauts/hackfortress-exchanger). 
This component connects to a UNIX Domain Socket that the
[hackfortress-exchanger](https://github.com/UWFCybernauts/hackfortress-exchanger)
hosts. Any functions called in the Hackfortress SourcePawn plugin that utilize this extension cause 
communication from this extension through the UNIX Domain Socket (recieved by hackfortress-exchanger).
This component can then perform actions based upon the data arriving through the UNIX Domain Socket. 

### Reasons for this implementation
We have implemented these components this way in order to avoid some issues that were occuring due 
to libstdc++, parrellization in SourceMod/TF2, and reconfiguring of entire libraries to match
compatible compile targets enforced by SourceMod/TF2. This method of implementation allows
any exchanger to be written in any higher level language that has a method of interfacing with 
UNIX Domain Sockets without needing to match 32bit compile targets or disabling RTTI. 

### Build instructions
This code requires the linux platform.
1) Clone the repository (and it's submodules)
2) Issue the command `make extension` in the root of the repo and watch the magic happen

The build shared object library is output to ./build/extension/hackfortress.ext.so

Add that shared object library to your `sourcemod/extensions/` directory and load the extension in the sourcemod
console.

### Authors
This component of UWF Cyber Security Club's Hackfortress Implementation is created and maintained 
by:
* Michael Mitchell (@AWildBeard)
