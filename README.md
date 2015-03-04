# NDNFS

Port of NDN file system based on [work](https://github.com/wentaoshang/NDNFS) by Wentao and Qiuhan.

See the file [INSTALL.md](https://github.com/zhehaowang/ndnfs-port/blob/master/INSTALL.md) for build and install instructions.

Report bug to Zhehao. wangzhehao410305@gmail.com

### Usage

NDNFS is an NDN-friendly file system. When mounted, data in the file system can be fetched via NDN through NDNFS-server.

To run on Mac:
<pre>
    $ mkdir /tmp/ndnfs
    $ mkdir /tmp/dir
    $ ./build/ndnfs -s [actual folder path] [mount point path]
</pre>
[Actual folder path] is where files are actually stored on the local file system; while [mount point path] is the mount point.

'-s' flag tells fuse to run single threaded.

Use '-d' flag to see all debug output of ndnfs:
<pre>
    $ ./build/ndnfs -d /tmp/dir /tmp/ndnfs
</pre>
Use '-f' flag to run in foreground and see debug info:
<pre>
    $ ./build/ndnfs -s -f /tmp/dir /tmp/ndnfs
</pre>
If '-f' is used, NDNFS is unmounted automatically when you kill 'ndnfs' process.

To unmount NDNFS, type:
<pre>
    $ umount /tmp/ndnfs
</pre>
To force unmount, use '-f' flag:
<pre>
    $ umount -f /tmp/ndnfs
</pre>

To configure ndnfs files prefix, use '-o prefix=\<prefix\>'; to configure log file path, usr '-o log=\<log file path\>'.

For example,
<pre>
    $ ./build/ndnfs /tmp/dir /tmp/ndnfs -o prefix=/ndn/broadcast/ndnfs -o log=ndnfs.log
</pre>
will mount /tmp/dir as /tmp/ndnfs, using prefix "/ndn/broadcast/ndnfs", and writing logs to ndnfs.log in running directory.

Please note that current implementation does not scan files that already exists in actual path, before running ndnfs.

For files to become available via NDNFS-server, please put them into mount point after running NDNFS

### NDNFS-server

NDNFS-server supports read access of NDNFS by remote through NDN.

To run on Mac:

Install and configure [NFD](https://github.com/named-data/NFD) before running the FS server.

Run:
<pre>
    $ ./build/ndnfs-server
</pre>
Use '-p' flag to configure prefix, '-d' flag to select db file, and '-f' flag to identify file system root (these should be the same with NDNFS configuration). Use '-l' flag to configure log file path. 

For example,
<pre>
    $ ./build/ndnfs-server -p /ndn/broadcast/ndnfs -l ndnfs-server.log -f /tmp/ndnfs
</pre>
will serve content in mount point /tmp/ndnfs, using prefix "/ndn/broadcast/ndnfs", and writing logs to ndnfs-server.log in running directory.

### NDNFS-client

To access NDNFS data remotely, please use [NDN-JS Firefox addon](https://github.com/named-data/ndn-js/blob/master/ndn-protocol.xpi?raw=true), preferably [experimental addon](https://github.com/zhehaowang/ndn-js/blob/plugin-update/ndn-protocol.xpi?raw=true) with adaptations made specific for ndnfs; 
Or a built-in client in tests.

**Instructions for Firefox addon:**
* Run nfd locally;
* Set the Firefox addon's hub to localhost if it's not already localhost;
* nfdc to the host of ndnfs-server or ndn testbed (can be localhost as well, in which case nfdc won't be needed);
* Type in a "\<prefix\>/\<file or folder\>" path as URI and fetch.

Right now, Firefox addon will try to infer the mimetype of the file based on extension, and invoke default behavior for the given mimetype. (.pdf being an exception: Download dialogue is called, instead of pdf.js)

Default behavior For NDNFS content with unknown mimetype is save as file.

**Instructions for client application:**
* Run nfd locally;
* nfdc to the host of ndnfs-server or ndn testbed (not needed if ndnfs server runs locally);
* Run client application;
<pre>
    $ ./build/test-client
</pre>
* To browse the metadata of a certain file or directory, in the running client, type in "show \<prefix\>/\<file or folder\>";
* To fetch a certain file and save it locally, in the running client, type in "fetch \<prefix\>/\<file or folder\> \<local save path\>".

Please note that in branch "browser-dir-listing" (default branch), only "fetch" command is supported.

Consider switching to "main" if testing with the client application.

### New features
* Instead of the network-ready data packets, store only the signature in sqlite3 database, and assemble NDN data packets when requested;
* Publish mime_type in a new meta-info branch;
* Updated to work with NDNJS Firefox addon, and latest version of NDN-CPP;
* Sign asynchronously (experimental, and still in local branch).
