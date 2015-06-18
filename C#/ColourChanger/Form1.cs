using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GranthamColour
{
    public partial class Form1 : Form
    {
        bool Red;
        bool Blue;
        bool Green;
        bool Yellow;
        bool White;
        bool Black;
        SolidBrush myBrush;


        public Form1()
        {
            InitializeComponent();
            this.listBox1.DrawItem +=
        new System.Windows.Forms.DrawItemEventHandler(this.listBox1_DrawItem);

            myBrush = new SolidBrush(Color.Black);     //instantiates the brush
        }


        private void listBox1_DrawItem(object sender, System.Windows.Forms.DrawItemEventArgs e)
        {
            //
            // Draw the background of the ListBox control for each item.
            // Create a new Brush and initialize to a Black colored brush
            // by default.
            //
            e.DrawBackground();
            

            // Draw the current item text based on the current 
            // Font and the custom brush settings.
            //
            e.Graphics.DrawString(((ListBox)sender).Items[e.Index].ToString(),
                e.Font, myBrush, e.Bounds, StringFormat.GenericDefault);
            //
            // If the ListBox has focus, draw a focus rectangle 
            // around the selected item.
            //
            e.DrawFocusRectangle();
        }


        void Form1_Click(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }




        private void Form1_DragEnter(object sender, DragEventArgs e)
        {

            e.Effect = DragDropEffects.Move;

        }

        private void Form1_DragDrop(object sender, DragEventArgs e)
        {

            int x = this.PointToClient(new Point(e.X, e.Y)).X;

            int y = this.PointToClient(new Point(e.X, e.Y)).Y;


        }

        private void button1_Click(object sender, EventArgs e)
        {
            List<string> number = new List<string>();
            number.Add("Number 1");
            number.Add("Number 2");
            number.Add("Number 3");
            number.Add("Number 4");
            number.Add("Number 5");
            number.Add("Number 6");
            number.Add("Number 7");
            number.Add("Number 8");



            listBox1.DataSource = number;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            
                if (!Red)        //tests if the colour is purple
                {                   //if its not, set it to purple
                    myBrush.Color = Color.Red;  //setting the colour to red
                    Red = true;  //sets the bool to true
                }

                else                //otherwise
                {
                    myBrush.Color = Color.Black;   //set the colour to black
                    Red = false;             //Set the bool to false
                }
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (!Blue)        //tests if the colour is purple
            {                   //if its not, set it to purple
                myBrush.Color = Color.Blue;  //setting the colour to blue
                Blue = true;  //sets the bool to true
            }

           else                //otherwise
            {
                myBrush.Color = Color.Black;   //set the colour to black
                Blue = false;             //Set the bool to false
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (!Green)        //tests if the colour is purple
            {                   //if its not, set it to purple
                myBrush.Color = Color.Green;  //setting the colour to green
                Green = true;  //sets the bool to true
            }

            else                //otherwise
            {
                myBrush.Color = Color.Black;   //set the colour to black
                Green = false;             //Set the bool to false
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (!Yellow)        //tests if the colour is purple
            {                   //if its not, set it to purple
                myBrush.Color = Color.Yellow;  //setting the colour to yellow
                Yellow = true;  //sets the bool to true
            }

            else                //otherwise
            {
                myBrush.Color = Color.Black;   //set the colour to black
                Yellow = false;             //Set the bool to false
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (!White)
            {
            myBrush.Color = Color.White;  //setting the colour to white
                White = true;  //sets the bool to true
            }

            else                //otherwise
            {
                myBrush.Color = Color.Black;   //set the colour to black
                White = false;             //Set the bool to false
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (!Black)
            {
                myBrush.Color = Color.Black;  //setting the colour to Black
                Black = true;  //sets the bool to true
            }

            else                //otherwise
            {
                myBrush.Color = Color.Black;   //set the colour to black
                Black = false;             //Set the bool to false
            }
        }
            
            
              

       
    }
}
