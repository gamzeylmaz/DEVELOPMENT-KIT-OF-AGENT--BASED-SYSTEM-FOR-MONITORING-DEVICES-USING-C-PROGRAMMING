using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace project
{
    public partial class Form1 : Form
    {
        
        
        

        public Form1()
        {
            InitializeComponent();
            serialPort1.Open();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void serialPort1_DataReceived(object sender,SerialDataReceivedEventArgs e)
        {

            this.Invoke(new EventHandler(displaydata_event));
           


        }
        private void serialPort2_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            this.Invoke(new EventHandler(displaydata_event2));



        }

        private void displaydata_event(object sender, EventArgs e)
        {
            int x_axis = pictureBox1.Location.X; // x ve y koordinatlarý
            int y_axis = pictureBox1.Location.Y;
            // int data_recive =int.Parse( serialPort1.ReadLine());
            string my_info = serialPort1.ReadLine();
            bool Password = my_info.Contains("sifre ");
            bool PanelLeft = my_info.Contains("left");
            bool PanelMiddle = my_info.Contains("middle");
            bool PanelRight = my_info.Contains("right");
            bool UserLala = my_info.Contains("lala");
            bool UserPo = my_info.Contains("po");
            bool DoorControl = my_info.Contains("white");
            if (PanelLeft)
            {
                x_axis = 590; y_axis = 75;
                pictureBox1.Location = new Point(x_axis, y_axis);
            }

            if (PanelMiddle)
            {
                x_axis = 423; y_axis = 75;
                pictureBox1.Location = new Point(x_axis, y_axis);
            }

            if (PanelRight)
            {
                x_axis = 260; y_axis = 75;
                pictureBox1.Location = new Point(x_axis, y_axis);
            }

            if (Password)
            {
                string password =my_info.Substring(6); 
                PasswordText.Text = password;
            }

            if (UserLala)
            {
               
                POTXT.Text = "";
                LALATXT.Text= @"Name = LALA
SKIN COLOR = YELLOW
SHAPE = NODE";
                
            }

            if (UserPo)
            {
                
                LALATXT.Text = "";

               POTXT.Text=@"Name = PO 
SKIN COLOR = RED
SHAPE = CIRCLE";
               
            }

           if (DoorControl)
            {

                MessageBox.Show(@"SOME ONE ON THE DOOR
PLEASE ENTER PASSWORD", "SECURTY WARNING", MessageBoxButtons.OK, MessageBoxIcon.Warning);
         
                
               
            }
           
        }
        private void displaydata_event2(object sender, EventArgs e)
        {

            int data_recive = int.Parse(serialPort1.ReadLine());

            PasswordText.Text = data_recive.ToString();


        }

        private void dogru_Click(object sender, EventArgs e)
        {
            int value = 270;
            serialPort1.WriteLine(value.ToString());
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int value = 184;
            serialPort1.WriteLine(value.ToString());
            
        }

       

       
        private void pictureBox4_Click(object sender, EventArgs e)
        {
            int value = 3;
            serialPort1.WriteLine(value.ToString());
            // serialPort1.WriteLine("CIRCLE");
        }

        

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            int value = 1;
            serialPort1.WriteLine(value.ToString());
            //serialPort1.WriteLine("TRIANGLE");
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            int value = 2;
            serialPort1.WriteLine(value.ToString());
            //serialPort1.WriteLine("SQUARE");
        }

        private void pictureBox5_Click(object sender, EventArgs e)
        {
            int value = 4;
            serialPort1.WriteLine(value.ToString());
            //serialPort1.WriteLine("RECTANGLE");
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
          
        }

        private void PnlSol_Click(object sender, EventArgs e)
        {
            int value = 5;
            serialPort1.WriteLine(value.ToString());
        }

        private void PnlOrta_Click(object sender, EventArgs e)
        {
            int value = 90;
            serialPort1.WriteLine(value.ToString());
        }

        private void PnlSag_Click(object sender, EventArgs e)
        {
            int value = 180;
            serialPort1.WriteLine(value.ToString());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int value = 360;
            serialPort1.WriteLine(value.ToString());
            int value2 = 540;
            serialPort1.WriteLine(value2.ToString());
        }

        private void pictureBox6_Click(object sender, EventArgs e)
        {
            int value = 6;
            serialPort1.WriteLine(value.ToString());
        }

        private void pictureBox7_Click(object sender, EventArgs e)
        {
            int value = 7;
            serialPort1.WriteLine(value.ToString());
        }

        private void pictureBox8_Click(object sender, EventArgs e)
        {
            int value = 8;
            serialPort1.WriteLine(value.ToString());
        }

        private void pictureBox9_Click(object sender, EventArgs e)
        {
            int value = 9;
            serialPort1.WriteLine(value.ToString());
        }
    }
}
