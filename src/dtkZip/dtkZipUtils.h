/* dtkZipUtils.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun 21 12:11:05 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 21 15:16:11 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 72
 */

/* Commentary: 
 * See credits inline.
 */

/* Change log:
 * 
 */

#ifndef DTKZIPUTILS_H
#define DTKZIPUTILS_H

#include "dtkZipExport.h"

#ifndef _ZLIB_H
#include "zlib.h"
#endif

// /////////////////////////////////////////////////////////////////
// Crypt
// /////////////////////////////////////////////////////////////////

/* crypt.h -- base code for crypt/uncrypt ZIPfile


   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   This code is a modified version of crypting code in Infozip distribution

   The encryption/decryption parts of this source code (as opposed to the
   non-echoing password parts) were originally written in Europe.  The
   whole source package can be freely distributed, including from the USA.
   (Prior to January 2000, re-export from the US was a violation of US law.)

   This encryption code is a direct transcription of the algorithm from
   Roger Schlafly, described by Phil Katz in the file appnote.txt.  This
   file (appnote.txt) is distributed with the PKZIP program (even in the
   version without encryption capabilities).

   If you don't need crypting in your application, just define symbols
   NOCRYPT and NOUNCRYPT.

   This code support the "Traditional PKWARE Encryption".

   The new AES encryption added on Zip format by Winzip (see the page
   http://www.winzip.com/aes_info.htm ) and PKWare PKZip 5.x Strong
   Encryption is not supported.
*/

#define CRC32(c, b) ((*(pcrc_32_tab+(((int)(c) ^ (b)) & 0xff))) ^ ((c) >> 8))

/***********************************************************************
 * Return the next byte in the pseudo-random sequence
 */
static int decrypt_byte(unsigned long* pkeys, const unsigned long* pcrc_32_tab)
{
    //(void) pcrc_32_tab; /* avoid "unused parameter" warning */
    unsigned temp;  /* POTENTIAL BUG:  temp*(temp^1) may overflow in an
                     * unpredictable manner on 16-bit systems; not a problem
                     * with any known compiler so far, though */

    temp = ((unsigned)(*(pkeys+2)) & 0xffff) | 2;
    return (int)(((temp * (temp ^ 1)) >> 8) & 0xff);
}

/***********************************************************************
 * Update the encryption keys with the next byte of plain text
 */
static int update_keys(unsigned long* pkeys,const unsigned long* pcrc_32_tab,int c)
{
    (*(pkeys+0)) = CRC32((*(pkeys+0)), c);
    (*(pkeys+1)) += (*(pkeys+0)) & 0xff;
    (*(pkeys+1)) = (*(pkeys+1)) * 134775813L + 1;
    {
        register int keyshift = (int)((*(pkeys+1)) >> 24);
        (*(pkeys+2)) = CRC32((*(pkeys+2)), keyshift);
    }
    return c;
}


/***********************************************************************
 * Initialize the encryption keys and the random header according to
 * the given password.
 */
static void init_keys(const char* passwd,unsigned long* pkeys,const unsigned long* pcrc_32_tab)
{
    *(pkeys+0) = 305419896L;
    *(pkeys+1) = 591751049L;
    *(pkeys+2) = 878082192L;
    while (*passwd != '\0') {
        update_keys(pkeys,pcrc_32_tab,(int)*passwd);
        passwd++;
    }
}

#define zdecode(pkeys,pcrc_32_tab,c)                                    \
    (update_keys(pkeys,pcrc_32_tab,c ^= decrypt_byte(pkeys,pcrc_32_tab)))

#define zencode(pkeys,pcrc_32_tab,c,t)                                  \
    (t=decrypt_byte(pkeys,pcrc_32_tab), update_keys(pkeys,pcrc_32_tab,c), t^(c))

// #ifdef INCLUDECRYPTINGCODE_IFCRYPTALLOWED

#define RAND_HEAD_LEN  12
/* "last resort" source for second part of crypt seed pattern */
#  ifndef ZCR_SEED2
#    define ZCR_SEED2 3141592654UL     /* use PI as default pattern */
#  endif

#include <stdlib.h>
#include <time.h>

static int crypthead(
    const char *passwd,         /* password string */
    unsigned char *buf,         /* where to write header */
    int bufSize,
    unsigned long* pkeys,
    const unsigned long* pcrc_32_tab,
    unsigned long crcForCrypting)
{
    int n;                       /* index in random header */
    int t;                       /* temporary */
    int c;                       /* random byte */
    unsigned char header[RAND_HEAD_LEN-2]; /* random header */
    static unsigned calls = 0;   /* ensure different random header each time */

    if (bufSize<RAND_HEAD_LEN)
        return 0;

    /* First generate RAND_HEAD_LEN-2 random bytes. We encrypt the
     * output of rand() to get less predictability, since rand() is
     * often poorly implemented.
     */
    if (++calls == 1)
    {
        srand((unsigned)(time(NULL) ^ ZCR_SEED2));
    }
    init_keys(passwd, pkeys, pcrc_32_tab);
    for (n = 0; n < RAND_HEAD_LEN-2; n++)
    {
        c = (rand() >> 7) & 0xff;
        header[n] = (unsigned char)zencode(pkeys, pcrc_32_tab, c, t);
    }
    /* Encrypt random header (last two bytes is high word of crc) */
    init_keys(passwd, pkeys, pcrc_32_tab);
    for (n = 0; n < RAND_HEAD_LEN-2; n++)
    {
        buf[n] = (unsigned char)zencode(pkeys, pcrc_32_tab, header[n], t);
    }
    buf[n++] = zencode(pkeys, pcrc_32_tab, (int)(crcForCrypting >> 16) & 0xff, t);
    buf[n++] = zencode(pkeys, pcrc_32_tab, (int)(crcForCrypting >> 24) & 0xff, t);
    return n;
}

// #endif

// /////////////////////////////////////////////////////////////////
// IOApi
// /////////////////////////////////////////////////////////////////

#define ZLIB_FILEFUNC_SEEK_CUR (1)
#define ZLIB_FILEFUNC_SEEK_END (2)
#define ZLIB_FILEFUNC_SEEK_SET (0)

#define ZLIB_FILEFUNC_MODE_READ      (1)
#define ZLIB_FILEFUNC_MODE_WRITE     (2)
#define ZLIB_FILEFUNC_MODE_READWRITEFILTER (3)

#define ZLIB_FILEFUNC_MODE_EXISTING (4)
#define ZLIB_FILEFUNC_MODE_CREATE   (8)


#ifndef ZCALLBACK

#if (defined(WIN32) || defined (WINDOWS) || defined (_WINDOWS)) && defined(CALLBACK) && defined (USEWINDOWS_CALLBACK)
#define ZCALLBACK CALLBACK
#else
#define ZCALLBACK
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

    typedef voidpf (ZCALLBACK *open_file_func) OF((voidpf opaque, voidpf file, int mode));
    typedef uLong  (ZCALLBACK *read_file_func) OF((voidpf opaque, voidpf stream, void* buf, uLong size));
    typedef uLong  (ZCALLBACK *write_file_func) OF((voidpf opaque, voidpf stream, const void* buf, uLong size));
    typedef uLong   (ZCALLBACK *tell_file_func) OF((voidpf opaque, voidpf stream));
    typedef int   (ZCALLBACK *seek_file_func) OF((voidpf opaque, voidpf stream, uLong offset, int origin));
    typedef int    (ZCALLBACK *close_file_func) OF((voidpf opaque, voidpf stream));
    typedef int    (ZCALLBACK *testerror_file_func) OF((voidpf opaque, voidpf stream));

    typedef struct zlib_filefunc_def_s
    {
        open_file_func      zopen_file;
        read_file_func      zread_file;
        write_file_func     zwrite_file;
        tell_file_func      ztell_file;
        seek_file_func      zseek_file;
        close_file_func     zclose_file;
        testerror_file_func zerror_file;
        voidpf              opaque;
    } zlib_filefunc_def;

    void fill_qiodevice_filefunc OF((zlib_filefunc_def* pzlib_filefunc_def));

#define ZREAD(filefunc,filestream,buf,size) ((*((filefunc).zread_file))((filefunc).opaque,filestream,buf,size))
#define ZWRITE(filefunc,filestream,buf,size) ((*((filefunc).zwrite_file))((filefunc).opaque,filestream,buf,size))
#define ZTELL(filefunc,filestream) ((*((filefunc).ztell_file))((filefunc).opaque,filestream))
#define ZSEEK(filefunc,filestream,pos,mode) ((*((filefunc).zseek_file))((filefunc).opaque,filestream,pos,mode))
#define ZCLOSE(filefunc,filestream) ((*((filefunc).zclose_file))((filefunc).opaque,filestream))
#define ZERROR(filefunc,filestream) ((*((filefunc).zerror_file))((filefunc).opaque,filestream))

#ifdef __cplusplus
}
#endif

// /////////////////////////////////////////////////////////////////
// JlCompress
// /////////////////////////////////////////////////////////////////

#include <QtCore>

class dtkZip;

class DTKZIP_EXPORT JlCompress {
private:
    static bool compressFile(dtkZip* zip, QString fileName, QString fileDest);
    static bool compressSubDir(dtkZip* parentZip, QString dir, QString parentDir, bool recursive = true);
    static bool extractFile(dtkZip* zip, QString fileName, QString fileDest);

    static bool removeFile(QStringList listFile);

public:
    static bool compressFile(QString fileCompressed, QString file);
    static bool compressFiles(QString fileCompressed, QStringList files);
    static bool compressDir(QString fileCompressed, QString dir = QString(), bool recursive = true);

public:
    static QString extractFile(QString fileCompressed, QString file, QString fileDest = QString());
    static QStringList extractFiles(QString fileCompressed, QStringList files, QString dir = QString());
    static QStringList extractDir(QString fileCompressed, QString dir = QString());
    static QStringList getFileList(QString fileCompressed);
};

// /////////////////////////////////////////////////////////////////
// quachecksum
// /////////////////////////////////////////////////////////////////

/// Checksum interface.
/** \class dtkChecksum32 quachecksum32.h <quazip/quachecksum32.h>
 * This is an interface for 32 bit checksums.
 * Classes implementing this interface can calcunate a certin
 * checksum in a single step:
 * \code
 * QChecksum32 *crc32 = new dtkCrc32(); 
 * rasoult = crc32->calculate(data);
 * \endcode
 * or by streaming the data:
 * \code
 * QChecksum32 *crc32 = new dtkCrc32(); 
 * while(!fileA.atEnd())
 *     crc32->update(fileA.read(bufSize));
 * resoultA = crc32->value();
 * crc32->reset();
 * while(!fileB.atEnd())
 *     crc32->update(fileB.read(bufSize));
 * resoultB = crc32->value();
 * \endcode
 */
class DTKZIP_EXPORT dtkChecksum32
{

public:
    ///Calculates the checksum for data.
    /** \a data source data
     * \return data checksum
     *
     * This function has no efect on the value returned by value().
     */
    virtual quint32 calculate(const QByteArray &data) = 0;

    ///Resets the calculation on a checksun for a stream.
    virtual void reset() = 0;

    ///Updates the calculated checksum for the stream
    /** \a buf next portion of data from the stream
     */
    virtual void update(const QByteArray &buf) = 0;

    ///Value of the checksum calculated for the stream passed throw update().
    /** \return checksum
     */
    virtual quint32 value() = 0;
};

// /////////////////////////////////////////////////////////////////
// quaadler32
// /////////////////////////////////////////////////////////////////

/// Adler32 checksum
/** \class dtkAdler32 quaadler32.h <quazip/quaadler32.h>
 * This class wrappers the adler32 function with the dtkChecksum32 interface.
 * See dtkChecksum32 for more info.
 */
class dtkAdler32 : public dtkChecksum32
{
public:
    dtkAdler32();

    quint32 calculate(const QByteArray &data);

    void reset();
    void update(const QByteArray &buf);
    quint32 value();

private:
    quint32 checksum;
};

// /////////////////////////////////////////////////////////////////
// quacrc32
// /////////////////////////////////////////////////////////////////

///CRC32 checksum
/** \class dtkCrc32 quacrc32.h <quazip/quacrc32.h>
 * This class wrappers the crc32 function with the dtkChecksum32 interface.
 * See dtkChecksum32 for more info.
 */

class DTKZIP_EXPORT dtkCrc32 : public dtkChecksum32
{
public:
    dtkCrc32();

    quint32 calculate(const QByteArray &data);

    void reset();
    void update(const QByteArray &buf);
    quint32 value();

private:
    quint32 checksum;
};

// /////////////////////////////////////////////////////////////////
// zip
// /////////////////////////////////////////////////////////////////

/* zip.h -- IO for compress .zip files using zlib
   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   This unzip package allow creates .ZIP file, compatible with PKZip 2.04g
   WinZip, InfoZip tools and compatible.
   Multi volume ZipFile (span) are not supported.
   Encryption compatible with pkzip 2.04g only supported
   Old compressions used by old PKZip 1.x are not supported

   For uncompress .zip file, look at unzip.h


   I WAIT FEEDBACK at mail info@winimage.com
   Visit also http://www.winimage.com/zLibDll/unzip.html for evolution

   Condition of use and distribution are the same than zlib :

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
   3. This notice may not be removed or altered from any source distribution.

   Modified by Sergey A. Tachenov to integrate with Qt.


*/

/* for more info about .ZIP format, see
   http://www.info-zip.org/pub/infozip/doc/appnote-981119-iz.zip
   http://www.info-zip.org/pub/infozip/doc/
   PkWare has also a specification at :
   ftp://ftp.pkware.com/probdesc.zip
*/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(STRICTZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
   from (void*) without cast */
    typedef struct TagzipFile__ { int unused; } zipFile__;
    typedef zipFile__ *zipFile;
#else
    typedef voidp zipFile;
#endif

#define ZIP_OK                          (0)
#define ZIP_EOF                         (0)
#define ZIP_ERRNO                       (Z_ERRNO)
#define ZIP_PARAMERROR                  (-102)
#define ZIP_BADZIPFILE                  (-103)
#define ZIP_INTERNALERROR               (-104)

#ifndef DEF_MEM_LEVEL
#  if MAX_MEM_LEVEL >= 8
#    define DEF_MEM_LEVEL 8
#  else
#    define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#  endif
#endif
/* default memLevel */

/* tm_zip contain date/time info */
    typedef struct tm_zip_s
    {
        uInt tm_sec;            /* seconds after the minute - [0,59] */
        uInt tm_min;            /* minutes after the hour - [0,59] */
        uInt tm_hour;           /* hours since midnight - [0,23] */
        uInt tm_mday;           /* day of the month - [1,31] */
        uInt tm_mon;            /* months since January - [0,11] */
        uInt tm_year;           /* years - [1980..2044] */
    } tm_zip;

    typedef struct
    {
        tm_zip      tmz_date;       /* date in understandable format           */
        uLong       dosDate;       /* if dos_date == 0, tmu_date is used      */
/*    uLong       flag;        */   /* general purpose bit flag        2 bytes */

        uLong       internal_fa;    /* internal file attributes        2 bytes */
        uLong       external_fa;    /* external file attributes        4 bytes */
    } zip_fileinfo;

    typedef const char* zipcharpc;


#define APPEND_STATUS_CREATE        (0)
#define APPEND_STATUS_CREATEAFTER   (1)
#define APPEND_STATUS_ADDINZIP      (2)

    extern zipFile ZEXPORT zipOpen OF((voidpf file, int append));
/*
  Create a zipfile.
  file is whatever the IO API accepts. For Qt IO API it's a pointer to
  QIODevice. For fopen() IO API it's a file name (const char*).
  if the file pathname exist and append==APPEND_STATUS_CREATEAFTER, the zip
  will be created at the end of the file.
  (useful if the file contain a self extractor code)
  if the file pathname exist and append==APPEND_STATUS_ADDINZIP, we will
  add files in existing zip (be sure you don't add file that doesn't exist)
  If the zipfile cannot be opened, the return value is NULL.
  Else, the return value is a zipFile Handle, usable with other function
  of this zip package.
*/

/* Note : there is no delete function into a zipfile.
   If you want delete file into a zipfile, you must open a zipfile, and create another
   Of couse, you can use RAW reading and writing to copy the file you did not want delte
*/

    extern zipFile ZEXPORT zipOpen2 OF((voidpf file,
                                        int append,
                                        zipcharpc* globalcomment,
                                        zlib_filefunc_def* pzlib_filefunc_def));

    extern int ZEXPORT zipOpenNewFileInZip OF((zipFile file,
                                               const char* filename,
                                               const zip_fileinfo* zipfi,
                                               const void* extrafield_local,
                                               uInt size_extrafield_local,
                                               const void* extrafield_global,
                                               uInt size_extrafield_global,
                                               const char* comment,
                                               int method,
                                               int level));
/*
  Open a file in the ZIP for writing.
  filename : the filename in zip (if NULL, '-' without quote will be used
  *zipfi contain supplemental information
  if extrafield_local!=NULL and size_extrafield_local>0, extrafield_local
  contains the extrafield data the the local header
  if extrafield_global!=NULL and size_extrafield_global>0, extrafield_global
  contains the extrafield data the the local header
  if comment != NULL, comment contain the comment string
  method contain the compression method (0 for store, Z_DEFLATED for deflate)
  level contain the level of compression (can be Z_DEFAULT_COMPRESSION)
*/


    extern int ZEXPORT zipOpenNewFileInZip2 OF((zipFile file,
                                                const char* filename,
                                                const zip_fileinfo* zipfi,
                                                const void* extrafield_local,
                                                uInt size_extrafield_local,
                                                const void* extrafield_global,
                                                uInt size_extrafield_global,
                                                const char* comment,
                                                int method,
                                                int level,
                                                int raw));

/*
  Same than zipOpenNewFileInZip, except if raw=1, we write raw file
*/

    extern int ZEXPORT zipOpenNewFileInZip3 OF((zipFile file,
                                                const char* filename,
                                                const zip_fileinfo* zipfi,
                                                const void* extrafield_local,
                                                uInt size_extrafield_local,
                                                const void* extrafield_global,
                                                uInt size_extrafield_global,
                                                const char* comment,
                                                int method,
                                                int level,
                                                int raw,
                                                int windowBits,
                                                int memLevel,
                                                int strategy,
                                                const char* password,
                                                uLong crcForCtypting));

/*
  Same than zipOpenNewFileInZip2, except
  windowBits,memLevel,,strategy : see parameter strategy in deflateInit2
  password : crypting password (NULL for no crypting)
  crcForCtypting : crc of file to compress (needed for crypting)
*/


    extern int ZEXPORT zipWriteInFileInZip OF((zipFile file,
                                               const void* buf,
                                               unsigned len));
/*
  Write data in the zipfile
*/

    extern int ZEXPORT zipCloseFileInZip OF((zipFile file));
/*
  Close the current file in the zipfile
*/

    extern int ZEXPORT zipCloseFileInZipRaw OF((zipFile file,
                                                uLong uncompressed_size,
                                                uLong crc32));
/*
  Close the current file in the zipfile, for fiel opened with
  parameter raw=1 in zipOpenNewFileInZip2
  uncompressed_size and crc32 are value for the uncompressed size
*/

    extern int ZEXPORT zipClose OF((zipFile file,
                                    const char* global_comment));
/*
  Close the zipfile
*/

#ifdef __cplusplus
}
#endif

// /////////////////////////////////////////////////////////////////
// unzip
// /////////////////////////////////////////////////////////////////

/* unzip.h -- IO for uncompress .zip files using zlib
   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant

   This unzip package allow extract file from .ZIP file, compatible with PKZip 2.04g
   WinZip, InfoZip tools and compatible.

   Multi volume ZipFile (span) are not supported.
   Encryption compatible with pkzip 2.04g only supported
   Old compressions used by old PKZip 1.x are not supported


   I WAIT FEEDBACK at mail info@winimage.com
   Visit also http://www.winimage.com/zLibDll/unzip.htm for evolution

   Condition of use and distribution are the same than zlib :

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
   3. This notice may not be removed or altered from any source distribution.

   Modified by Sergey A. Tachenov to integrate with Qt.


*/

/* for more info about .ZIP format, see
   http://www.info-zip.org/pub/infozip/doc/appnote-981119-iz.zip
   http://www.info-zip.org/pub/infozip/doc/
   PkWare has also a specification at :
   ftp://ftp.pkware.com/probdesc.zip
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ZLIB_H
#include "zlib.h"
#endif

#ifndef _ZLIBIOAPI_H
#include "dtkZipUtils.h"
#endif

#if defined(STRICTUNZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
   from (void*) without cast */
    typedef struct TagunzFile__ { int unused; } unzFile__;
    typedef unzFile__ *unzFile;
#else
    typedef voidp unzFile;
#endif


#define UNZ_OK                          (0)
#define UNZ_END_OF_LIST_OF_FILE         (-100)
#define UNZ_ERRNO                       (Z_ERRNO)
#define UNZ_EOF                         (0)
#define UNZ_PARAMERROR                  (-102)
#define UNZ_BADZIPFILE                  (-103)
#define UNZ_INTERNALERROR               (-104)
#define UNZ_CRCERROR                    (-105)

/* tm_unz contain date/time info */
    typedef struct tm_unz_s
    {
        uInt tm_sec;            /* seconds after the minute - [0,59] */
        uInt tm_min;            /* minutes after the hour - [0,59] */
        uInt tm_hour;           /* hours since midnight - [0,23] */
        uInt tm_mday;           /* day of the month - [1,31] */
        uInt tm_mon;            /* months since January - [0,11] */
        uInt tm_year;           /* years - [1980..2044] */
    } tm_unz;

/* unz_global_info structure contain global data about the ZIPfile
   These data comes from the end of central dir */
    typedef struct unz_global_info_s
    {
        uLong number_entry;         /* total number of entries in
                                       the central dir on this disk */
        uLong size_comment;         /* size of the global comment of the zipfile */
    } unz_global_info;


/* unz_file_info contain information about a file in the zipfile */
    typedef struct unz_file_info_s
    {
        uLong version;              /* version made by                 2 bytes */
        uLong version_needed;       /* version needed to extract       2 bytes */
        uLong flag;                 /* general purpose bit flag        2 bytes */
        uLong compression_method;   /* compression method              2 bytes */
        uLong dosDate;              /* last mod file date in Dos fmt   4 bytes */
        uLong crc;                  /* crc-32                          4 bytes */
        uLong compressed_size;      /* compressed size                 4 bytes */
        uLong uncompressed_size;    /* uncompressed size               4 bytes */
        uLong size_filename;        /* filename length                 2 bytes */
        uLong size_file_extra;      /* extra field length              2 bytes */
        uLong size_file_comment;    /* file comment length             2 bytes */

        uLong disk_num_start;       /* disk number start               2 bytes */
        uLong internal_fa;          /* internal file attributes        2 bytes */
        uLong external_fa;          /* external file attributes        4 bytes */

        tm_unz tmu_date;
    } unz_file_info;

    extern int ZEXPORT unzStringFileNameCompare OF ((const char* fileName1,
                                                     const char* fileName2,
                                                     int iCaseSensitivity));
/*
  Compare two filename (fileName1,fileName2).
  If iCaseSenisivity = 1, comparision is case sensitivity (like strcmp)
  If iCaseSenisivity = 2, comparision is not case sensitivity (like strcmpi
  or strcasecmp)
  If iCaseSenisivity = 0, case sensitivity is defaut of your operating system
  (like 1 on Unix, 2 on Windows)
*/


    extern unzFile ZEXPORT unzOpen OF((voidpf file));
/*
  Open a Zip file. path contain whatever zopen_file from the IO API
  accepts. For Qt implementation it is a pointer to QIODevice, for
  fopen() implementation it's a file name.
  If the zipfile cannot be opened (file don't exist or in not valid), the
  return value is NULL.
  Else, the return value is a unzFile Handle, usable with other function
  of this unzip package.
*/

    extern unzFile ZEXPORT unzOpen2 OF((voidpf file,
                                        zlib_filefunc_def* pzlib_filefunc_def));
/*
  Open a Zip file, like unzOpen, but provide a set of file low level API
  for read/write the zip file (see ioapi.h)
*/

    extern int ZEXPORT unzClose OF((unzFile file));
/*
  Close a ZipFile opened with unzipOpen.
  If there is files inside the .Zip opened with unzOpenCurrentFile (see later),
  these files MUST be closed with unzipCloseCurrentFile before call unzipClose.
  return UNZ_OK if there is no problem. */

    extern int ZEXPORT unzGetGlobalInfo OF((unzFile file,
                                            unz_global_info *pglobal_info));
/*
  Write info about the ZipFile in the *pglobal_info structure.
  No preparation of the structure is needed
  return UNZ_OK if there is no problem. */


    extern int ZEXPORT unzGetGlobalComment OF((unzFile file,
                                               char *szComment,
                                               uLong uSizeBuf));
/*
  Get the global comment string of the ZipFile, in the szComment buffer.
  uSizeBuf is the size of the szComment buffer.
  return the number of byte copied or an error code <0
*/


/***************************************************************************/
/* Unzip package allow you browse the directory of the zipfile */

    extern int ZEXPORT unzGoToFirstFile OF((unzFile file));
/*
  Set the current file of the zipfile to the first file.
  return UNZ_OK if there is no problem
*/

    extern int ZEXPORT unzGoToNextFile OF((unzFile file));
/*
  Set the current file of the zipfile to the next file.
  return UNZ_OK if there is no problem
  return UNZ_END_OF_LIST_OF_FILE if the actual file was the latest.
*/

    extern int ZEXPORT unzLocateFile OF((unzFile file,
                                         const char *szFileName,
                                         int iCaseSensitivity));
/*
  Try locate the file szFileName in the zipfile.
  For the iCaseSensitivity signification, see unzStringFileNameCompare

  return value :
  UNZ_OK if the file is found. It becomes the current file.
  UNZ_END_OF_LIST_OF_FILE if the file is not found
*/


/* ****************************************** */
/* Ryan supplied functions */
/* unz_file_info contain information about a file in the zipfile */
    typedef struct unz_file_pos_s
    {
        uLong pos_in_zip_directory;   /* offset in zip file directory */
        uLong num_of_file;            /* # of file */
    } unz_file_pos;

    extern int ZEXPORT unzGetFilePos(
        unzFile file,
        unz_file_pos* file_pos);

    extern int ZEXPORT unzGoToFilePos(
        unzFile file,
        unz_file_pos* file_pos);

/* ****************************************** */

    extern int ZEXPORT unzGetCurrentFileInfo OF((unzFile file,
                                                 unz_file_info *pfile_info,
                                                 char *szFileName,
                                                 uLong fileNameBufferSize,
                                                 void *extraField,
                                                 uLong extraFieldBufferSize,
                                                 char *szComment,
                                                 uLong commentBufferSize));
/*
  Get Info about the current file
  if pfile_info!=NULL, the *pfile_info structure will contain somes info about
  the current file
  if szFileName!=NULL, the filemane string will be copied in szFileName
  (fileNameBufferSize is the size of the buffer)
  if extraField!=NULL, the extra field information will be copied in extraField
  (extraFieldBufferSize is the size of the buffer).
  This is the Central-header version of the extra field
  if szComment!=NULL, the comment string of the file will be copied in szComment
  (commentBufferSize is the size of the buffer)
*/

/***************************************************************************/
/* for reading the content of the current zipfile, you can open it, read data
   from it, and close it (you can close it before reading all the file)
*/

    extern int ZEXPORT unzOpenCurrentFile OF((unzFile file));
/*
  Open for reading data the current file in the zipfile.
  If there is no error, the return value is UNZ_OK.
*/

    extern int ZEXPORT unzOpenCurrentFilePassword OF((unzFile file,
                                                      const char* password));
/*
  Open for reading data the current file in the zipfile.
  password is a crypting password
  If there is no error, the return value is UNZ_OK.
*/

    extern int ZEXPORT unzOpenCurrentFile2 OF((unzFile file,
                                               int* method,
                                               int* level,
                                               int raw));
/*
  Same than unzOpenCurrentFile, but open for read raw the file (not uncompress)
  if raw==1
  *method will receive method of compression, *level will receive level of
  compression
  note : you can set level parameter as NULL (if you did not want known level,
  but you CANNOT set method parameter as NULL
*/

    extern int ZEXPORT unzOpenCurrentFile3 OF((unzFile file,
                                               int* method,
                                               int* level,
                                               int raw,
                                               const char* password));
/*
  Same than unzOpenCurrentFile, but open for read raw the file (not uncompress)
  if raw==1
  *method will receive method of compression, *level will receive level of
  compression
  note : you can set level parameter as NULL (if you did not want known level,
  but you CANNOT set method parameter as NULL
*/


    extern int ZEXPORT unzCloseCurrentFile OF((unzFile file));
/*
  Close the file in zip opened with unzOpenCurrentFile
  Return UNZ_CRCERROR if all the file was read but the CRC is not good
*/

    extern int ZEXPORT unzReadCurrentFile OF((unzFile file,
                                              voidp buf,
                                              unsigned len));
/*
  Read bytes from the current file (opened by unzOpenCurrentFile)
  buf contain buffer where data must be copied
  len the size of buf.

  return the number of byte copied if somes bytes are copied
  return 0 if the end of file was reached
  return <0 with error code if there is an error
  (UNZ_ERRNO for IO error, or zLib error for uncompress error)
*/

    extern z_off_t ZEXPORT unztell OF((unzFile file));
/*
  Give the current position in uncompressed data
*/

    extern int ZEXPORT unzeof OF((unzFile file));
/*
  return 1 if the end of file was reached, 0 elsewhere
*/

    extern int ZEXPORT unzGetLocalExtrafield OF((unzFile file,
                                                 voidp buf,
                                                 unsigned len));
/*
  Read extra field from the current file (opened by unzOpenCurrentFile)
  This is the local-header version of the extra field (sometimes, there is
  more info in the local-header version than in the central-header)

  if buf==NULL, it return the size of the local extra field

  if buf!=NULL, len is the size of the buffer, the extra header is copied in
  buf.
  the return value is the number of bytes copied in buf, or (if <0)
  the error code
*/

/***************************************************************************/

/* Get the current file offset */
    extern uLong ZEXPORT unzGetOffset (unzFile file);

/* Set the current file offset */
    extern int ZEXPORT unzSetOffset (unzFile file, uLong pos);

#ifdef __cplusplus
}
#endif

#endif
