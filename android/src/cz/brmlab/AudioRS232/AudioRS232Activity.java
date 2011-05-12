package cz.brmlab.AudioRS232;

import android.app.Activity;
import android.os.Bundle;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.AudioFormat;
import android.media.MediaRecorder;

public class AudioRS232Activity extends Activity {

	public short[] soundplay;
	public short[] soundrec;
	public AudioTrack audiotrack;
	public AudioRecord audiorecord;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
	}

	@Override
	protected void onResume() {
		super.onResume();

		setupSound();
		Thread thread = new Thread(new Runnable() {
			public void run() {
				processSound();
			}
		});
		thread.start();
	}

	void setupSound() {
		int minPlaySize = AudioTrack.getMinBufferSize(48000,
				AudioFormat.CHANNEL_CONFIGURATION_STEREO,
				AudioFormat.ENCODING_PCM_16BIT);
		int minRecSize = AudioRecord.getMinBufferSize(48000,
				AudioFormat.CHANNEL_CONFIGURATION_STEREO,
				AudioFormat.ENCODING_PCM_16BIT);

		soundplay = new short[minPlaySize];
		soundrec = new short[minRecSize];
		for (int i = 0; i < minPlaySize; ++i) {
			soundplay[i] = (short)(i * 30000 / minPlaySize);
		}
		audiotrack = new AudioTrack(AudioManager.STREAM_MUSIC, 48000,
				AudioFormat.CHANNEL_CONFIGURATION_STEREO,
				AudioFormat.ENCODING_PCM_16BIT, minPlaySize,
				AudioTrack.MODE_STREAM);
		audiorecord = new AudioRecord(
				MediaRecorder.AudioSource.MIC, 48000,
				AudioFormat.CHANNEL_CONFIGURATION_MONO,
				AudioFormat.ENCODING_PCM_16BIT, minRecSize);
		audiotrack.play();
		audiorecord.startRecording();
	}

	void processSound() {
		audiotrack.write(soundplay, 0, soundplay.length);
		audiorecord.read(soundrec, 0, soundrec.length);
	}

}
