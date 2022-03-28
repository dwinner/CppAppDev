// MediaLAN 02/2013
// CRtspSession
// - JPEG test image simulaton

// These are the 4 simulated JPEG images of the tutorial RTP streamer.
// We just have the JPEG scan data. JPEG Headers are stripped off because the belonging
// information is tranmitted in the RTP JPEG payload header (see RFC 2435 for that)
// The images are small enough to fit into just one RTP packet. Otherwise fragmentation
// would be necessary.

#ifndef _JPEG_SAMPLES_H
#define _JPEG_SAMPLES_H

#define KJpegCh1ScanDataLen 32
#define KJpegCh2ScanDataLen 56

extern char JpegScanDataCh1A[];
extern char JpegScanDataCh1B[];

extern char JpegScanDataCh2A[];
extern char JpegScanDataCh2B[];

#endif
