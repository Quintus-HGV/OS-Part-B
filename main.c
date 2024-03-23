#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vlc/vlc.h>
#include <pthread.h>

// Structure to hold data for the media player
struct MediaData {
    libvlc_instance_t *vlcInstance;
    libvlc_media_player_t *mediaPlayer;
    pthread_t mediaThread;
};

// Structure to hold media player state
struct MediaPlayer {
    int isPlaying;
    int volume;
    char currentMedia[256];
    struct MediaData mediaData;
};

// Function to play media in a separate thread
void *playMediaThread(void *data) {
    struct MediaData *mediaData = (struct MediaData *)data;

    // Play the media
    libvlc_media_player_play(mediaData->mediaPlayer);

    // Wait for media to finish (this is a simple example, you might need a more sophisticated approach)
    sleep(10);

    // Stop the media player
    libvlc_media_player_stop(mediaData->mediaPlayer);

    pthread_exit(NULL);
}

// Initialize media player
void initializeMediaPlayer(struct MediaPlayer *player) {
    player->isPlaying = 0; // 0 for not playing, 1 for playing
    player->volume = 50;    // Initial volume level
    player->currentMedia[0] = '\0'; // Empty string for current media

    // Initialize libVLC
    player->mediaData.vlcInstance = libvlc_new(0, NULL);

    // Create a media player
    player->mediaData.mediaPlayer = libvlc_media_player_new(player->mediaData.vlcInstance);
}

// Play a media file
void playMedia(struct MediaPlayer *player, const char *media) {
    if (!player->isPlaying) {
        printf("Playing: %s\n", media);
        player->isPlaying = 1;
        snprintf(player->currentMedia, sizeof(player->currentMedia), "%s", media);

        // Load the selected media file
        libvlc_media_t *vlcMedia = libvlc_media_new_path(player->mediaData.vlcInstance, media);
        libvlc_media_player_set_media(player->mediaData.mediaPlayer, vlcMedia);
        libvlc_media_release(vlcMedia);

        // Create a thread for media playback
        if (pthread_create(&player->mediaData.mediaThread, NULL, playMediaThread, (void *)&player->mediaData) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Media player is already playing. Stop current playback first.\n");
    }
}

// Stop media playback
void stopMedia(struct MediaPlayer *player) {
    if (player->isPlaying) {
        printf("Stopping playback\n");
        player->isPlaying = 0;

        // Wait for the media thread to finish
        pthread_join(player->mediaData.mediaThread, NULL);

        player->currentMedia[0] = '\0';
    } else {
        printf("Media player is not currently playing.\n");
    }
}

// Adjust volume
void adjustVolume(struct MediaPlayer *player, int delta) {
    player->volume += delta;

    // Ensure volume stays within valid range (0 to 100)
    if (player->volume < 0) {
        player->volume = 0;
    } else if (player->volume > 100) {
        player->volume = 100;
    }

    printf("Volume adjusted to: %d\n", player->volume);
}

// Release media player and libVLC instance
void releaseMediaPlayer(struct MediaPlayer *player) {
    libvlc_media_player_release(player->mediaData.mediaPlayer);
    libvlc_release(player->mediaData.vlcInstance);
}

// List video files using the "ls" command
void listVideoFiles() {
    printf("Available video files in the current directory:\n");
    system("ls *.mp4 *.avi *.mkv");
}

// Get user input for the video file to play
void getUserInput(char *videoFile) {
    printf("Enter the name of the video file to play: ");
    scanf("%s", videoFile);
}

int main() {
    // Create and initialize the media player
    struct MediaPlayer myMediaPlayer;
    initializeMediaPlayer(&myMediaPlayer);

    // List available video files
    listVideoFiles();

    // Get user input for the video file to play
    char videoFile[256];
    getUserInput(videoFile);

    // Simulate API calls
    playMedia(&myMediaPlayer, videoFile);
    adjustVolume(&myMediaPlayer, 10);
    stopMedia(&myMediaPlayer);

    // Release media player resources
    releaseMediaPlayer(&myMediaPlayer);

    return 0;
}
