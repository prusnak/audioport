package cz.brmlab.AudioRS232;

import java.text.CharacterIterator;
import java.text.StringCharacterIterator;
import java.util.LinkedList;
import java.util.Queue;

import android.media.AudioFormat;
import android.media.AudioManager;
//import android.media.AudioRecord;
import android.media.AudioTrack;
//import android.media.MediaRecorder;

public class AudioRS232 {

	private Queue<Character> b1;
	private Queue<Character> b2;
	private short[] soundplay;
//	private short[] soundrec;
	private AudioTrack audiotrack;
//	private AudioRecord audiorecord;
	private int bufSize = 9600;

	public AudioRS232() {
		b1 = new LinkedList<Character>();
		b2 = new LinkedList<Character>();
		soundplay = new short[bufSize];
//		soundrec = new short[bufSize];
		for (int i = 0; i < bufSize; ++i) {
			soundplay[i] = (short)(i * 30000 / bufSize);
		}
		audiotrack = new AudioTrack(AudioManager.STREAM_MUSIC, 48000, AudioFormat.CHANNEL_CONFIGURATION_STEREO, AudioFormat.ENCODING_PCM_16BIT, bufSize * 2, AudioTrack.MODE_STREAM);
//		audiorecord = new AudioRecord(MediaRecorder.AudioSource.MIC, 48000, AudioFormat.CHANNEL_CONFIGURATION_MONO, AudioFormat.ENCODING_PCM_16BIT, bufSize * 2);
		audiotrack.play();
//		audiorecord.startRecording();
	}

	public void send(String str) {
		CharacterIterator it = new StringCharacterIterator(str);
		for (char c = it.first(); c != CharacterIterator.DONE; c = it.next()) {
			b1.add(c);
		}
	}

	public void send2(String str) {
		CharacterIterator it = new StringCharacterIterator(str);
		for (char c = it.first(); c != CharacterIterator.DONE; c = it.next()) {
			b2.add(c);
		}
	}

	public void loop() {
		// audiotrack.write(soundplay, 0, soundplay.length * 2);
	}

}
