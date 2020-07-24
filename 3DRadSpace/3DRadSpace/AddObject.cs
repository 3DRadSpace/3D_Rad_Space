using _3DRadSpaceDll;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _3DRadSpace
{
	public partial class AddObject : Form
	{
		public AddObject()
		{
			InitializeComponent();
		}
		public _3DRadSpaceDll.GameObject Result { get; set; }
		private void pictureBox1_Click(object sender, EventArgs e)
		{

		}

		private void pictureBox10_Click(object sender, EventArgs e)
		{
			ScriptW script = new ScriptW();
			if(script.ShowDialog() == DialogResult.OK)
			{
				Result = script.Result;
			}
			script.Dispose();
			Close();
		}

		private void PictureBox15_Click(object sender, EventArgs e)
		{
			CameraW camera = new CameraW();
			if(camera.ShowDialog() == DialogResult.OK)
			{
				Result = camera.Result;
			}
			camera.Dispose();
			Close();
		}

		private void pictureBox17_Click(object sender, EventArgs e)
		{
			SkyColorW skyColor = new SkyColorW();
			if(skyColor.ShowDialog() == DialogResult.OK)
			{
				Result = skyColor.Result;
			}
			skyColor.Dispose();
			Close();
		}

		private void pictureBox19_Click(object sender, EventArgs e)
		{
			FogW fog = new FogW();
			if(fog.ShowDialog() == DialogResult.OK)
			{
				Result = fog.Result;
			}
			fog.Dispose();
			Close();
		}

		private void pictureBox16_Click(object sender, EventArgs e)
		{
			SkinmeshW skinmesh = new SkinmeshW();
			if(skinmesh.ShowDialog() == DialogResult.OK)
			{
				Result = skinmesh.Result;
			}
			skinmesh.Dispose();
			Close();
		}

		private void pictureBox2_Click(object sender, EventArgs e)
		{
			SpriteW sprite = new SpriteW();
			if(sprite.ShowDialog() == DialogResult.OK)
			{
				Result = sprite.Result;
			}
			sprite.Dispose();
			Close();
		}

		private void pictureBox3_Click(object sender, EventArgs e)
		{
			TextPrintW textPrint = new TextPrintW();
			if (textPrint.ShowDialog() == DialogResult.OK) Result = textPrint.Result;
			textPrint.Dispose();
			Close();
		}

		private void pictureBox4_Click(object sender, EventArgs e)
		{

		}

		private void pictureBox21_Click(object sender, EventArgs e)
		{
			SoundEffectW soundEffectW = new SoundEffectW();
			if (soundEffectW.ShowDialog() == DialogResult.OK) Result = soundEffectW.Result;
			soundEffectW.Dispose();
			Close();
		}

		private void pictureBox9_Click(object sender, EventArgs e)
		{
			ExitFadeW exitFade = new ExitFadeW();
			if (exitFade.ShowDialog() == DialogResult.OK) Result = exitFade.Result;
			exitFade.Dispose();
			Close();
		}

		private void pictureBox6_Click(object sender, EventArgs e)
		{
			EventOnKeyW EOK = new EventOnKeyW();
			if (EOK.ShowDialog() == DialogResult.OK) Result = EOK.Result;
			EOK.Dispose();
			Close();
		}

		private void pictureBox5_Click(object sender, EventArgs e)
		{
			EventOnLocationW EOL = new EventOnLocationW();
			if (EOL.ShowDialog() == DialogResult.OK) Result = EOL.Result;
			EOL.Dispose();
			Close();
		}

		private void pictureBox8_Click(object sender, EventArgs e)
		{
			TimerW timer = new TimerW();
			if (timer.ShowDialog() == DialogResult.OK) Result = timer.Result;
			timer.Dispose();
			Close();
		}

		private void pictureBox24_Click(object sender, EventArgs e)
		{
			GameSettingsW gameSettings = new GameSettingsW();
			if(gameSettings.ShowDialog() == DialogResult.OK) Editor.GraphcalSettings = gameSettings.Result;
			gameSettings.Dispose();
			Close();
		}

		private void pictureBox20_Click(object sender, EventArgs e)
		{
			SoundSourceW soundSourceW = new SoundSourceW();
			if (soundSourceW.ShowDialog() == DialogResult.OK) Result = soundSourceW.Result;
			soundSourceW.Dispose();
			Close();
		}

		private void pictureBox18_Click(object sender, EventArgs e)
		{
			SkyBoxW skyboxw = new SkyBoxW();
			if (skyboxw.ShowDialog() == DialogResult.OK) Result = skyboxw.Result;
			skyboxw.Dispose();
			Close();
		}

		private void pictureBox26_Click(object sender, EventArgs e)
		{
			FPVCameraW cameraW = new FPVCameraW();
			if (cameraW.ShowDialog() == DialogResult.OK) Result = cameraW.Result;
			cameraW.Dispose();
			Close();
		}

		private void pictureBox27_Click(object sender, EventArgs e)
		{
			CounterW counterW = new CounterW();
			if (counterW.ShowDialog() == DialogResult.OK) Result = counterW.Result;
			counterW.Dispose();
			Close();
		}

        private void pictureBox28_Click(object sender, EventArgs e)
        {
			GroupW groupW = new GroupW();
			if (groupW.ShowDialog() == DialogResult.OK) Result = groupW.Result;
			groupW.Dispose();
			Close();
        }
    }
}
