package com.android.game;

public class GameActivity extends android.app.NativeActivity
{
	static
	{
		System.loadLibrary("openal");
		System.loadLibrary("sndfile");
		System.loadLibrary("game");
	}
}
