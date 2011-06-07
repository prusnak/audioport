package cz.brmlab.AudioPort;

import java.text.CharacterIterator;
import java.text.StringCharacterIterator;
import java.util.LinkedList;
import java.util.Queue;

import android.media.AudioFormat;
import android.media.AudioManager;
//import android.media.AudioRecord;
import android.media.AudioTrack;
//import android.media.MediaRecorder;

public class AudioPort {

	private Queue<Character> queue;
	private short[] soundplay;
//	private short[] soundrec;
	private AudioTrack audiotrack;
//	private AudioRecord audiorecord;
	private int bufSize = 9600;

	public AudioPort() {
		queue = new LinkedList<Character>();
		soundplay = new short[bufSize];
//		soundrec = new short[bufSize];
		audiotrack = new AudioTrack(AudioManager.STREAM_MUSIC, 48000, AudioFormat.CHANNEL_CONFIGURATION_STEREO, AudioFormat.ENCODING_PCM_16BIT, bufSize * 2, AudioTrack.MODE_STREAM);
//		audiorecord = new AudioRecord(MediaRecorder.AudioSource.MIC, 48000, AudioFormat.CHANNEL_CONFIGURATION_MONO, AudioFormat.ENCODING_PCM_16BIT, bufSize * 2);
		audiotrack.play();
//		audiorecord.startRecording();
	}

	public void send(String str) {
		CharacterIterator it = new StringCharacterIterator(str);
		for (char c = it.first(); c != CharacterIterator.DONE; c = it.next()) {
			queue.add(c);
		}
	}

	public void loop() {
		for (;;) {
			convertSend();
			audiotrack.write(soundplay, 0, soundplay.length * 2);
		}
	}

	public void convertSend() {
		for (int i = 0; i < bufSize; ++i) {
			soundplay[i] = (short)(880 * (i/2) % 32000);
		}
	}

}
