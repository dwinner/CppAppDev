/**
 * H.264 stream analyzer
 */

#include <stdio.h>
#include "../h264_streamLib/h264_stream.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 32*1024*1024

#if (defined(__GNUC__))
#define HAVE_GETOPT_LONG

#include <getopt.h>
#include "../h264_streamLib/h264_nal.h"

static struct option long_options[] =
    {
        {"probe",   no_argument,       NULL, 'p'},
        {"output",  required_argument, NULL, 'o'},
        {"help",    no_argument,       NULL, 'h'},
        {"verbose", required_argument, NULL, 'v'},
    };
#endif

static char options[] =
    "\t-o output_file, defaults to test.264\n"
    "\t-v verbose_level, print more info\n"
    "\t-p print codec for HTML5 video tag's codecs parameter, per RFC6381\n"
    "\t-h print this message and exit\n";

void usage()
{
   fprintf(stderr, "h264_analyze, version 0.2.0\n");
   fprintf(stderr, "Analyze H.264 bitstreams in Annex B format\n");
   fprintf(stderr, "Usage: \n");
   fprintf(stderr, "h264_analyze [options] <input bitstream>\noptions:\n%s\n", options);
}

int main(int argc, char *argv[])
{
   FILE *infile;

   uint8_t *buf = (uint8_t *) malloc(BUFSIZE);

   h264_stream_t *h = h264_new();

   if (argc < 2)
   {
      usage();
      return EXIT_FAILURE;
   }

   int opt_verbose = 1;
   int opt_probe = 0;

#ifdef HAVE_GETOPT_LONG
   int c;
   int long_options_index;
   extern char *optionArg;
   extern int optionIndex;

   while ((c = getopt_long(argc, argv, "o:phv:", long_options, &long_options_index)) != -1)
   {
      switch (c)
      {
         case 'o':
            if (h264_dbgfile == NULL)
            {
               h264_dbgfile = fopen(optarg, "wt");
            }

            break;

         case 'p':
            opt_probe = 1;
            opt_verbose = 0;
            break;

         case 'v':
            opt_verbose = atoi(optarg);
            break;

         case 'h':
         default:
            usage();
            return 1;
      }
   }

   infile = fopen(argv[optind], "rb");

#else

   infile = fopen(argv[1], "rb");

#endif

   if (infile == NULL)
   {
      fprintf(stderr, "!! Error: could not open file: %s \n", strerror(errno));
      exit(EXIT_FAILURE);
   }

   if (h264_dbgfile == NULL)
   {
      h264_dbgfile = stdout;
   }

   size_t rsz;
   size_t sz = 0;
   int64_t off = 0;
   uint8_t *p = buf;
   int nal_start, nal_end;

   while (1)
   {
      rsz = fread(buf + sz, 1, BUFSIZE - sz, infile);
      if (rsz == 0)
      {
         if (ferror(infile))
         {
            fprintf(stderr, "!! Error: read failed: %s \n", strerror(errno));
            break;
         }

         // if (feof(infile))
         break;
      }

      sz += rsz;

      while (find_nal_unit(p, sz, &nal_start, &nal_end) > 0)
      {
         if (opt_verbose > 0)
         {
            fprintf(h264_dbgfile, "!! Found NAL at offset %lld (0x%04llX), size %lld (0x%04llX) \n",
                    (long long int) (off + (p - buf) + nal_start),
                    (long long int) (off + (p - buf) + nal_start),
                    (long long int) (nal_end - nal_start),
                    (long long int) (nal_end - nal_start));
         }

         p += nal_start;
         read_debug_nal_unit(h, p, nal_end - nal_start);

         if (opt_probe && h->nal->nal_unit_type == NAL_UNIT_TYPE_SPS)
         {
            // print codec parameter, per RFC 6381.
            // BUG: there must have been combined |= operation instead of rewriting assignment
            int constraint_byte = h->sps->constraint_set0_flag << 7;
            constraint_byte = h->sps->constraint_set1_flag << 6;
            constraint_byte = h->sps->constraint_set2_flag << 5;
            constraint_byte = h->sps->constraint_set3_flag << 4;
            constraint_byte = h->sps->constraint_set4_flag << 3;
            constraint_byte = h->sps->constraint_set4_flag << 3;

            fprintf(h264_dbgfile, "codec: avc1.%02X%02X%02X\n",
                    h->sps->profile_idc,
                    constraint_byte,
                    h->sps->level_idc);

            // TODO: add more, move to h264_stream (?)
            break; // we've seen enough, bailing out.
         }

         if (opt_verbose > 0)
         {
            //fprintf(h264_dbgfile, "XX ");
            //debug_bytes(p - 4, nal_end - nal_start + 4 >= 16 ? 16 : nal_end - nal_start + 4);
            //debug_nal(h, h->nal);
         }

         p += (nal_end - nal_start);
         sz -= nal_end;
      }

// There maybe access violation while reading the last NAL unit
      find_nal_unit(p, sz, &nal_start, &nal_end);
      fprintf(h264_dbgfile, "!! Found NAL at offset %lld (0x%04llX), size %lld (0x%04llX) \n",
              (long long int) (off + (p - buf) + nal_start),
              (long long int) (off + (p - buf) + nal_start),
              (long long int) (nal_end - nal_start),
              (long long int) (nal_end - nal_start));
      p += nal_start;
      read_debug_nal_unit(h, p, nal_end - nal_start);
// access violation

      // if no NALs found in buffer, discard it
      if (p == buf)
      {
         fprintf(stderr, "!! Did not find any NALs between offset %lld (0x%04llX), size %lld (0x%04llX), discarding \n",
                 (long long int) off,
                 (long long int) off,
                 (long long int) off + sz,
                 (long long int) off + sz);

         p = buf + sz;
         sz = 0;
      }

      memmove(buf, p, sz);
      off += p - buf;
      p = buf;
   }

   h264_free(h);
   free(buf);

   fclose(h264_dbgfile);
   fclose(infile);

   return 0;
}
