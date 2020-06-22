namespace WindowsApplication
{
    partial class aHandControllerForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.aButtonContract = new System.Windows.Forms.Button();
            this.aButtonExtend = new System.Windows.Forms.Button();
            this.aTrackBarSpeed = new System.Windows.Forms.TrackBar();
            this.aLabelInfo = new System.Windows.Forms.Label();
            this.aListPortNames = new System.Windows.Forms.ListBox();
            this.aButtonConnect = new System.Windows.Forms.Button();
            this.aListBaudRates = new System.Windows.Forms.ListBox();
            this.aTextOutput = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.aTrackBarSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // aButtonContract
            // 
            this.aButtonContract.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonContract.Location = new System.Drawing.Point(612, 24);
            this.aButtonContract.Name = "aButtonContract";
            this.aButtonContract.Size = new System.Drawing.Size(145, 56);
            this.aButtonContract.TabIndex = 0;
            this.aButtonContract.Text = "Contract";
            this.aButtonContract.UseVisualStyleBackColor = true;
            this.aButtonContract.Click += new System.EventHandler(this.aButtonContract_Click);
            // 
            // aButtonExtend
            // 
            this.aButtonExtend.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonExtend.Location = new System.Drawing.Point(612, 96);
            this.aButtonExtend.Name = "aButtonExtend";
            this.aButtonExtend.Size = new System.Drawing.Size(145, 56);
            this.aButtonExtend.TabIndex = 1;
            this.aButtonExtend.Text = "Extend";
            this.aButtonExtend.UseVisualStyleBackColor = true;
            this.aButtonExtend.Click += new System.EventHandler(this.aButtonExtend_Click);
            // 
            // aTrackBarSpeed
            // 
            this.aTrackBarSpeed.Location = new System.Drawing.Point(534, 24);
            this.aTrackBarSpeed.Maximum = 3;
            this.aTrackBarSpeed.Minimum = 1;
            this.aTrackBarSpeed.Name = "aTrackBarSpeed";
            this.aTrackBarSpeed.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.aTrackBarSpeed.Size = new System.Drawing.Size(56, 128);
            this.aTrackBarSpeed.TabIndex = 2;
            this.aTrackBarSpeed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.aTrackBarSpeed.Value = 1;
            // 
            // aLabelInfo
            // 
            this.aLabelInfo.AutoSize = true;
            this.aLabelInfo.Location = new System.Drawing.Point(541, 174);
            this.aLabelInfo.Name = "aLabelInfo";
            this.aLabelInfo.Size = new System.Drawing.Size(78, 17);
            this.aLabelInfo.TabIndex = 3;
            this.aLabelInfo.Text = "Information";
            // 
            // aListPortNames
            // 
            this.aListPortNames.FormattingEnabled = true;
            this.aListPortNames.ItemHeight = 16;
            this.aListPortNames.Location = new System.Drawing.Point(46, 24);
            this.aListPortNames.Name = "aListPortNames";
            this.aListPortNames.Size = new System.Drawing.Size(120, 100);
            this.aListPortNames.TabIndex = 4;
            // 
            // aButtonConnect
            // 
            this.aButtonConnect.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.aButtonConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonConnect.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonConnect.Location = new System.Drawing.Point(46, 142);
            this.aButtonConnect.Name = "aButtonConnect";
            this.aButtonConnect.Size = new System.Drawing.Size(268, 30);
            this.aButtonConnect.TabIndex = 6;
            this.aButtonConnect.Text = "Connect";
            this.aButtonConnect.UseVisualStyleBackColor = false;
            this.aButtonConnect.Click += new System.EventHandler(this.aButtonConnect_Click);
            // 
            // aListBaudRates
            // 
            this.aListBaudRates.FormattingEnabled = true;
            this.aListBaudRates.ItemHeight = 16;
            this.aListBaudRates.Location = new System.Drawing.Point(194, 24);
            this.aListBaudRates.Name = "aListBaudRates";
            this.aListBaudRates.Size = new System.Drawing.Size(120, 100);
            this.aListBaudRates.TabIndex = 7;
            // 
            // aTextOutput
            // 
            this.aTextOutput.Location = new System.Drawing.Point(46, 253);
            this.aTextOutput.Multiline = true;
            this.aTextOutput.Name = "aTextOutput";
            this.aTextOutput.ReadOnly = true;
            this.aTextOutput.Size = new System.Drawing.Size(711, 165);
            this.aTextOutput.TabIndex = 8;
            // 
            // aHandControllerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.aTextOutput);
            this.Controls.Add(this.aListBaudRates);
            this.Controls.Add(this.aButtonConnect);
            this.Controls.Add(this.aListPortNames);
            this.Controls.Add(this.aLabelInfo);
            this.Controls.Add(this.aTrackBarSpeed);
            this.Controls.Add(this.aButtonExtend);
            this.Controls.Add(this.aButtonContract);
            this.Name = "aHandControllerForm";
            this.Text = "Hand Controller";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.aHandControllerForm_FormClosing);
            this.Load += new System.EventHandler(this.aHandControllerForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.aTrackBarSpeed)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button aButtonContract;
        private System.Windows.Forms.Button aButtonExtend;
        private System.Windows.Forms.TrackBar aTrackBarSpeed;
        private System.Windows.Forms.Label aLabelInfo;
        private System.Windows.Forms.ListBox aListPortNames;
        private System.Windows.Forms.Button aButtonConnect;
        private System.Windows.Forms.ListBox aListBaudRates;
        private System.Windows.Forms.TextBox aTextOutput;
    }
}

