using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using _3DRadSpaceDll;


namespace _3DRadSpace
{
    public partial class Script : Form
    {
        public Script()
        {
            InitializeComponent();
        }
        public string LoadedScript = "";
        private void SyntaxHighlighting()
        {
            int originalselection = richTextBox1.SelectionStart;
            richTextBox1.SelectionStart = 0;
            richTextBox1.SelectionLength = richTextBox1.Text.Length;
            richTextBox1.SelectionColor = Color.Black;
            richTextBox1.SelectionStart = originalselection;
            char[] text = richTextBox1.Text.ToCharArray();
            richTextBox1.SelectionLength = 0;
            if (checkBox2.Checked == false) return;

            for (int i=0; i < richTextBox1.Text.Length - 1; i++)
            {
                try
                {
                     if (text[i] == 'i' && text[i + 1] == 'n' && text[i + 2] == 't')
                     {
                         richTextBox1.SelectionStart = i;
                         richTextBox1.SelectionLength = 3;
                         richTextBox1.SelectionColor = Color.CornflowerBlue;
                     }
                   
                    if (text[i] == 'v' && text[i+1] == 'o' && text[i+2] == 'i' && text[i+3] == 'd')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 4;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == 'f' && text[i+1] == 'l' && text[i+2] == 'o' && text[i+3] == 'a' && text[i+4] == 't')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 5;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == 'b' && text[i+1] == 'o' && text[i+2] == 'o' && text[i+3] == 'l')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 4;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == 's' && text[i+1] == 't' && text[i+2] == 'r' && text[i+3] == 'i' && text[i+4] == 'n' && text[i+5] == 'g')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 6;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == 'n' && text [i+1] == 'u' && text[i+2] == 'l' && text[i+3] == 'l')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 4;
                        richTextBox1.SelectionColor = Color.Blue;
                    }
                    if (text[i] == 't' && text[i + 1] == 'r' && text[i + 2] == 'u' && text[i + 3] == 'e')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 4;
                        richTextBox1.SelectionColor = Color.Blue;
                    }
                    if (text[i] == 'f' && text[i + 1] == 'a' && text[i + 2] == 'l' && text[i + 3] == 's' && text[i + 4] == 'e')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 5;
                        richTextBox1.SelectionColor = Color.Blue;
                    }
                    if (text[i] == '0' || text[i] == '1' || text[i] == '2' || text[i] == '3' || text[i] == '4' || text[i] == '5' || text[i] == '6' || text[i] == '7' || text[i] == '8' || text[i] == '9' )
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 1;
                        richTextBox1.SelectionColor = Color.Red;
                    }
                    if(text[i]  == '{' || text[i] == '}' || text[i] == '(' || text[i] == ')')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 1;
                        richTextBox1.SelectionColor = Color.Violet;
                    }
                    if(text[i] == '"')
                    {
                        richTextBox1.SelectionStart = i;
                        for(int j =i+1; j <= richTextBox1.Text.Length; j++)
                        {
                            if (text[j] == '"')
                            {
                                richTextBox1.SelectionLength = j-i+1;
                                i = j + 1;
                                break;
                            }
                            else if(j == richTextBox1.Text.Length - 1)
                            {
                                richTextBox1.SelectionLength = 1;
                            }
                        }        
                        richTextBox1.SelectionColor = Color.ForestGreen;
                    }
                    if (text[i] == '\'')
                    {
                        for(int j = i+1 ; j <= richTextBox1.Text.Length; j++)
                        {
                            richTextBox1.SelectionStart = i;
                            if (text[j] == '\'')
                            {
                                richTextBox1.SelectionLength = 3;
                            }
                            else if(j == richTextBox1.Text.Length)
                            {
                                richTextBox1.SelectionLength = 1;
                            }
                            richTextBox1.SelectionColor = Color.Red;
                        }
                    }
                    if(text[i] == 'c' && text[i+1] == 'h' && text[i+2] == 'a' && text[i+3] == 'r')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 4;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == 'i' && text[i+1] == 'f')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 2;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == ';')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 1;
                        richTextBox1.SelectionColor = Color.DarkRed;
                    }
                    if(text[i] == 'r' && text[i+1] == 'e' && text[i+2] == 't' && text[i+3] == 'u' && text[i+4] == 'r' && text[i+5] == 'n')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 6;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    if(text[i] == '=' || text[i] == '-' || text[i] == '+' ||( text[i] == '/' && text[i+1] != '/' && text[i-1] != '/') || text[i] == '%' || text[i] == '*' || text[i] == '<' || text[i] == '>' || text[i] == '!')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 1;
                        richTextBox1.SelectionColor = Color.Pink;
                    }
                    if (text[i] == '/' && text[i + 1] == '/')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 2;
                        richTextBox1.SelectionColor = Color.Green;
                    }
                    if(text[i] == 'e' && text[i+1] == 'l' && text[i+2] == 's' && text[i+3] == 'e')
                    {
                        richTextBox1.SelectionStart = i;
                        richTextBox1.SelectionLength = 4;
                        richTextBox1.SelectionColor = Color.CornflowerBlue;
                    }
                    richTextBox1.SelectionStart = originalselection;
                    richTextBox1.SelectionLength = 0;
                }
                
                catch(IndexOutOfRangeException)
                {
                    
                }
            }
        }

        private void Script_Load(object sender, EventArgs e)
        {
            SyntaxHighlighting();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(LoadedScript))
            {
                File.WriteAllText(@"./CompiledScript/Script.3drss", richTextBox1.Text);
                LoadedScript = @"./CompiledScript/Script.3drss";
            }
            ScriptInterpeter.Run(ScriptInterpeter.Debug(LoadedScript));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog()
            {
                Filter = "3DRadSpace Script (*.3drss)| *.3drss",
                InitialDirectory = @"/Scripts/",
                Multiselect = false,
                Title = "Open a saved script to use for your project..."
            };
            openFile.ShowDialog();
            LoadedScript = openFile.FileName;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            File.WriteAllText(@"lastobj.data", " ");
            Close();
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            SyntaxHighlighting();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            string ObjData = "Script " + textBox1.Text + " " + checkBox1.Checked.ToString() + " "+LoadedScript;
            File.WriteAllText(@"lastobj.data", ObjData);
            Close();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog()
            {
                Title = "Save a project file.",
                Filter = "3DRadSpace Script (*.3drss)| *.3drss",
                OverwritePrompt = true,
                InitialDirectory = @"/Scripts/",
            };
            DialogResult save = saveFile.ShowDialog();
            if(save == DialogResult.OK)
            {
                File.WriteAllText(saveFile.FileName,richTextBox1.Text);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Process.Start(@".\Help Files\Script.rtf");
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            if(checkBox3.Checked == true) SyntaxHighlighting();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            SyntaxHighlighting();
        }

        private void domainUpDown1_SelectedItemChanged(object sender, EventArgs e)
        {
            richTextBox1.Font = new Font("Microsoft Sans Serif",Convert.ToInt32(numericUpDown1.Value) / 10);
        }
    }
}
