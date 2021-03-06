/*
 *   Playlist Class for Falcon Pi Player (FPP)
 *
 *   Copyright (C) 2013 the Falcon Pi Player Developers
 *      Initial development by:
 *      - David Pitts (dpitts)
 *      - Tony Mace (MyKroFt)
 *      - Mathew Mrosko (Materdaddy)
 *      - Chris Pinkham (CaptainMurdoch)
 *      For additional credits and developers, see credits.php.
 *
 *   The Falcon Pi Player (FPP) is free software; you can redistribute it
 *   and/or modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <stdbool.h>

#define PL_TYPE_BOTH			0
#define PL_TYPE_MEDIA			1
#define PL_TYPE_SEQUENCE		2
#define PL_TYPE_PAUSE			3
#define PL_TYPE_VIDEO			4 // deprecated, legacy v0.2.0 implementation
#define PL_TYPE_EVENT			5
#define PL_TYPE_PLUGIN_NEXT		6

// Actions to take during a running playlist
#define PL_ACTION_NOOP          0
#define PL_ACTION_STOP          1
#define PL_ACTION_PAUSE         2
#define PL_ACTION_NEXT_ITEM     3
#define PL_ACTION_PREV_ITEM     4

#define PAUSE_STATUS_IDLE		0
#define PAUSE_STATUS_STARTED	1
#define PAUSE_STATUS_ENDED		2

#define PLAYLIST_STOP_INDEX		-1

#define PL_MAX_ENTRIES			128


typedef struct {
	unsigned char type;
	char cType;
	char seqName[256];
	char songName[256];
	char eventID[6];
	unsigned int pauselength;
	char data[256];
} PlaylistEntry;

typedef struct {
	PlaylistEntry playList[PL_MAX_ENTRIES];
	char currentPlaylist[128];
	char currentPlaylistFile[128];
	int  playListCount;
	int  currentPlaylistEntry;
	int  StopPlaylist;
	int  ForceStop;
	int  playlistStarting;
	int  first;
	int  last;
	int  repeat;
} PlaylistDetails;

class Playlist {
  public:
	Playlist();
	~Playlist();

	void StopPlaylistGracefully(void);
	void StopPlaylistNow(void);
	void PlayListPlayingInit(void);
	void PlayListPlayingProcess(void);
	void PlayListPlayingCleanup(void);
	void PlaylistProcessMediaData(void);
	int  ParsePlaylistEntry(char *buf, PlaylistEntry *pe);

	int               m_playlistAction;
	PlaylistDetails   m_playlistDetails;
	int               m_numberOfSecondsPaused;

  private:

	void IncrementPlayListEntry(void);
	void DecrementPlayListEntry(void);
	void CalculateNextPlayListEntry(void);
	int  ReadPlaylist(char const * file);
	void PauseProcess(void);
	void PlayPlaylistEntry(bool calculateNext);
	void PlaylistPlaySong(void);
	void PlaylistPrint(void);

	struct timeval         m_pauseStartTime;
	struct timeval         m_nowTime;
	int                    m_pauseStatus;
};

extern Playlist         *playlist;

#endif
