﻿namespace WindowsApplication
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
            this.components = new System.ComponentModel.Container();
            this.aListPortNames = new System.Windows.Forms.ListBox();
            this.aButtonConnect = new System.Windows.Forms.Button();
            this.aListBaudRates = new System.Windows.Forms.ListBox();
            this.aTextOutput = new System.Windows.Forms.TextBox();
            this.aLabelPortName = new System.Windows.Forms.Label();
            this.aLabelBaudRate = new System.Windows.Forms.Label();
            this.aGroupConnection = new System.Windows.Forms.GroupBox();
            this.aButtonDisconnect = new System.Windows.Forms.Button();
            this.aRefreshButton = new System.Windows.Forms.Button();
            this.aTrackBarSpeed = new System.Windows.Forms.TrackBar();
            this.aGroupControls = new System.Windows.Forms.GroupBox();
            this.aLabelSetCharBufferTimeout = new System.Windows.Forms.Label();
            this.aButtonSetCharBufferTimeout = new System.Windows.Forms.Button();
            this.aTextboxSetCharBufferTimeout = new System.Windows.Forms.TextBox();
            this.aLabelSetCommandTimer = new System.Windows.Forms.Label();
            this.aButtonSetCommandTimer = new System.Windows.Forms.Button();
            this.aTextboxSetCommandTimer = new System.Windows.Forms.TextBox();
            this.aLabelSpeedValue = new System.Windows.Forms.Label();
            this.aButtonStop = new System.Windows.Forms.Button();
            this.aButtonExtend = new System.Windows.Forms.Button();
            this.aButtonContract = new System.Windows.Forms.Button();
            this.aLabelSpeed = new System.Windows.Forms.Label();
            this.aTextMicrocontroller = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.aTimerMicrocontrollerOutput = new System.Windows.Forms.Timer(this.components);
            this.aTimerContractButtonDown = new System.Windows.Forms.Timer(this.components);
            this.aTimerExtendButtonDown = new System.Windows.Forms.Timer(this.components);
            this.aGroupConnection.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.aTrackBarSpeed)).BeginInit();
            this.aGroupControls.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // aListPortNames
            // 
            this.aListPortNames.FormattingEnabled = true;
            this.aListPortNames.ItemHeight = 16;
            this.aListPortNames.Location = new System.Drawing.Point(22, 52);
            this.aListPortNames.Name = "aListPortNames";
            this.aListPortNames.Size = new System.Drawing.Size(120, 100);
            this.aListPortNames.TabIndex = 4;
            // 
            // aButtonConnect
            // 
            this.aButtonConnect.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aButtonConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonConnect.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonConnect.Location = new System.Drawing.Point(22, 205);
            this.aButtonConnect.Name = "aButtonConnect";
            this.aButtonConnect.Size = new System.Drawing.Size(262, 30);
            this.aButtonConnect.TabIndex = 6;
            this.aButtonConnect.Text = "Connect";
            this.aButtonConnect.UseVisualStyleBackColor = false;
            this.aButtonConnect.Click += new System.EventHandler(this.aButtonConnect_Click);
            // 
            // aListBaudRates
            // 
            this.aListBaudRates.FormattingEnabled = true;
            this.aListBaudRates.ItemHeight = 16;
            this.aListBaudRates.Location = new System.Drawing.Point(164, 52);
            this.aListBaudRates.Name = "aListBaudRates";
            this.aListBaudRates.Size = new System.Drawing.Size(120, 100);
            this.aListBaudRates.TabIndex = 7;
            // 
            // aTextOutput
            // 
            this.aTextOutput.BackColor = System.Drawing.SystemColors.Window;
            this.aTextOutput.ForeColor = System.Drawing.SystemColors.MenuText;
            this.aTextOutput.Location = new System.Drawing.Point(24, 365);
            this.aTextOutput.Multiline = true;
            this.aTextOutput.Name = "aTextOutput";
            this.aTextOutput.ReadOnly = true;
            this.aTextOutput.Size = new System.Drawing.Size(637, 120);
            this.aTextOutput.TabIndex = 8;
            // 
            // aLabelPortName
            // 
            this.aLabelPortName.AutoSize = true;
            this.aLabelPortName.Location = new System.Drawing.Point(19, 32);
            this.aLabelPortName.Name = "aLabelPortName";
            this.aLabelPortName.Size = new System.Drawing.Size(75, 17);
            this.aLabelPortName.TabIndex = 9;
            this.aLabelPortName.Text = "Port Name";
            // 
            // aLabelBaudRate
            // 
            this.aLabelBaudRate.AutoSize = true;
            this.aLabelBaudRate.Location = new System.Drawing.Point(161, 32);
            this.aLabelBaudRate.Name = "aLabelBaudRate";
            this.aLabelBaudRate.Size = new System.Drawing.Size(75, 17);
            this.aLabelBaudRate.TabIndex = 10;
            this.aLabelBaudRate.Text = "Baud Rate";
            // 
            // aGroupConnection
            // 
            this.aGroupConnection.BackColor = System.Drawing.Color.Silver;
            this.aGroupConnection.Controls.Add(this.aButtonDisconnect);
            this.aGroupConnection.Controls.Add(this.aRefreshButton);
            this.aGroupConnection.Controls.Add(this.aListPortNames);
            this.aGroupConnection.Controls.Add(this.aLabelBaudRate);
            this.aGroupConnection.Controls.Add(this.aButtonConnect);
            this.aGroupConnection.Controls.Add(this.aListBaudRates);
            this.aGroupConnection.Controls.Add(this.aLabelPortName);
            this.aGroupConnection.Location = new System.Drawing.Point(24, 24);
            this.aGroupConnection.Name = "aGroupConnection";
            this.aGroupConnection.Size = new System.Drawing.Size(307, 291);
            this.aGroupConnection.TabIndex = 11;
            this.aGroupConnection.TabStop = false;
            this.aGroupConnection.Text = "Connection";
            // 
            // aButtonDisconnect
            // 
            this.aButtonDisconnect.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aButtonDisconnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonDisconnect.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonDisconnect.Location = new System.Drawing.Point(22, 241);
            this.aButtonDisconnect.Name = "aButtonDisconnect";
            this.aButtonDisconnect.Size = new System.Drawing.Size(262, 30);
            this.aButtonDisconnect.TabIndex = 12;
            this.aButtonDisconnect.Text = "Disconnect";
            this.aButtonDisconnect.UseVisualStyleBackColor = false;
            this.aButtonDisconnect.Click += new System.EventHandler(this.aButtonDisconnect_Click);
            // 
            // aRefreshButton
            // 
            this.aRefreshButton.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aRefreshButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aRefreshButton.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aRefreshButton.Location = new System.Drawing.Point(22, 169);
            this.aRefreshButton.Name = "aRefreshButton";
            this.aRefreshButton.Size = new System.Drawing.Size(262, 30);
            this.aRefreshButton.TabIndex = 11;
            this.aRefreshButton.Text = "Refresh";
            this.aRefreshButton.UseVisualStyleBackColor = false;
            this.aRefreshButton.Click += new System.EventHandler(this.aRefreshButton_Click);
            // 
            // aTrackBarSpeed
            // 
            this.aTrackBarSpeed.LargeChange = 3;
            this.aTrackBarSpeed.Location = new System.Drawing.Point(15, 21);
            this.aTrackBarSpeed.Maximum = 5;
            this.aTrackBarSpeed.Minimum = 2;
            this.aTrackBarSpeed.Name = "aTrackBarSpeed";
            this.aTrackBarSpeed.Size = new System.Drawing.Size(188, 56);
            this.aTrackBarSpeed.TabIndex = 2;
            this.aTrackBarSpeed.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.aTrackBarSpeed.Value = 2;
            this.aTrackBarSpeed.Scroll += new System.EventHandler(this.aTrackBarSpeed_Scroll);
            // 
            // aGroupControls
            // 
            this.aGroupControls.BackColor = System.Drawing.Color.Silver;
            this.aGroupControls.Controls.Add(this.aLabelSetCharBufferTimeout);
            this.aGroupControls.Controls.Add(this.aButtonSetCharBufferTimeout);
            this.aGroupControls.Controls.Add(this.aTextboxSetCharBufferTimeout);
            this.aGroupControls.Controls.Add(this.aLabelSetCommandTimer);
            this.aGroupControls.Controls.Add(this.aButtonSetCommandTimer);
            this.aGroupControls.Controls.Add(this.aTextboxSetCommandTimer);
            this.aGroupControls.Controls.Add(this.aLabelSpeedValue);
            this.aGroupControls.Controls.Add(this.aButtonStop);
            this.aGroupControls.Controls.Add(this.aButtonExtend);
            this.aGroupControls.Controls.Add(this.aButtonContract);
            this.aGroupControls.Controls.Add(this.aLabelSpeed);
            this.aGroupControls.Controls.Add(this.aTrackBarSpeed);
            this.aGroupControls.Location = new System.Drawing.Point(354, 24);
            this.aGroupControls.Name = "aGroupControls";
            this.aGroupControls.Size = new System.Drawing.Size(307, 291);
            this.aGroupControls.TabIndex = 12;
            this.aGroupControls.TabStop = false;
            this.aGroupControls.Text = "Movement Controls";
            // 
            // aLabelSetCharBufferTimeout
            // 
            this.aLabelSetCharBufferTimeout.AutoSize = true;
            this.aLabelSetCharBufferTimeout.Location = new System.Drawing.Point(19, 218);
            this.aLabelSetCharBufferTimeout.Name = "aLabelSetCharBufferTimeout";
            this.aLabelSetCharBufferTimeout.Size = new System.Drawing.Size(135, 17);
            this.aLabelSetCharBufferTimeout.TabIndex = 19;
            this.aLabelSetCharBufferTimeout.Text = "Char Buffer Timeout";
            // 
            // aButtonSetCharBufferTimeout
            // 
            this.aButtonSetCharBufferTimeout.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aButtonSetCharBufferTimeout.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonSetCharBufferTimeout.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonSetCharBufferTimeout.Location = new System.Drawing.Point(157, 238);
            this.aButtonSetCharBufferTimeout.Name = "aButtonSetCharBufferTimeout";
            this.aButtonSetCharBufferTimeout.Size = new System.Drawing.Size(127, 30);
            this.aButtonSetCharBufferTimeout.TabIndex = 18;
            this.aButtonSetCharBufferTimeout.Text = "Set";
            this.aButtonSetCharBufferTimeout.UseVisualStyleBackColor = false;
            this.aButtonSetCharBufferTimeout.Click += new System.EventHandler(this.aButtonSetCharBufferTimeout_Click);
            // 
            // aTextboxSetCharBufferTimeout
            // 
            this.aTextboxSetCharBufferTimeout.Location = new System.Drawing.Point(22, 242);
            this.aTextboxSetCharBufferTimeout.Name = "aTextboxSetCharBufferTimeout";
            this.aTextboxSetCharBufferTimeout.Size = new System.Drawing.Size(127, 22);
            this.aTextboxSetCharBufferTimeout.TabIndex = 17;
            // 
            // aLabelSetCommandTimer
            // 
            this.aLabelSetCommandTimer.AutoSize = true;
            this.aLabelSetCommandTimer.Location = new System.Drawing.Point(19, 152);
            this.aLabelSetCommandTimer.Name = "aLabelSetCommandTimer";
            this.aLabelSetCommandTimer.Size = new System.Drawing.Size(182, 17);
            this.aLabelSetCommandTimer.TabIndex = 16;
            this.aLabelSetCommandTimer.Text = "Command Frequency Timer";
            // 
            // aButtonSetCommandTimer
            // 
            this.aButtonSetCommandTimer.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aButtonSetCommandTimer.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonSetCommandTimer.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonSetCommandTimer.Location = new System.Drawing.Point(157, 172);
            this.aButtonSetCommandTimer.Name = "aButtonSetCommandTimer";
            this.aButtonSetCommandTimer.Size = new System.Drawing.Size(127, 30);
            this.aButtonSetCommandTimer.TabIndex = 15;
            this.aButtonSetCommandTimer.Text = "Set";
            this.aButtonSetCommandTimer.UseVisualStyleBackColor = false;
            this.aButtonSetCommandTimer.Click += new System.EventHandler(this.aButtonSetCommandTimer_Click);
            // 
            // aTextboxSetCommandTimer
            // 
            this.aTextboxSetCommandTimer.Location = new System.Drawing.Point(22, 176);
            this.aTextboxSetCommandTimer.Name = "aTextboxSetCommandTimer";
            this.aTextboxSetCommandTimer.Size = new System.Drawing.Size(127, 22);
            this.aTextboxSetCommandTimer.TabIndex = 14;
            // 
            // aLabelSpeedValue
            // 
            this.aLabelSpeedValue.AutoSize = true;
            this.aLabelSpeedValue.Location = new System.Drawing.Point(264, 35);
            this.aLabelSpeedValue.Name = "aLabelSpeedValue";
            this.aLabelSpeedValue.Size = new System.Drawing.Size(16, 17);
            this.aLabelSpeedValue.TabIndex = 13;
            this.aLabelSpeedValue.Text = "2";
            // 
            // aButtonStop
            // 
            this.aButtonStop.BackColor = System.Drawing.Color.IndianRed;
            this.aButtonStop.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonStop.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonStop.Location = new System.Drawing.Point(22, 104);
            this.aButtonStop.Name = "aButtonStop";
            this.aButtonStop.Size = new System.Drawing.Size(262, 30);
            this.aButtonStop.TabIndex = 12;
            this.aButtonStop.Text = "Stop";
            this.aButtonStop.UseVisualStyleBackColor = false;
            this.aButtonStop.Click += new System.EventHandler(this.aButtonStop_Click);
            // 
            // aButtonExtend
            // 
            this.aButtonExtend.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aButtonExtend.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonExtend.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonExtend.Location = new System.Drawing.Point(157, 68);
            this.aButtonExtend.Name = "aButtonExtend";
            this.aButtonExtend.Size = new System.Drawing.Size(127, 30);
            this.aButtonExtend.TabIndex = 11;
            this.aButtonExtend.Text = "Extend";
            this.aButtonExtend.UseVisualStyleBackColor = false;
            this.aButtonExtend.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aButtonExtend_MouseDown);
            this.aButtonExtend.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aButtonExtend_MouseUp);
            // 
            // aButtonContract
            // 
            this.aButtonContract.BackColor = System.Drawing.Color.LightSkyBlue;
            this.aButtonContract.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F);
            this.aButtonContract.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.aButtonContract.Location = new System.Drawing.Point(22, 68);
            this.aButtonContract.Name = "aButtonContract";
            this.aButtonContract.Size = new System.Drawing.Size(127, 30);
            this.aButtonContract.TabIndex = 10;
            this.aButtonContract.Text = "Contract";
            this.aButtonContract.UseVisualStyleBackColor = false;
            this.aButtonContract.MouseDown += new System.Windows.Forms.MouseEventHandler(this.aButtonContract_MouseDown);
            this.aButtonContract.MouseUp += new System.Windows.Forms.MouseEventHandler(this.aButtonContract_MouseUp);
            // 
            // aLabelSpeed
            // 
            this.aLabelSpeed.AutoSize = true;
            this.aLabelSpeed.Location = new System.Drawing.Point(209, 35);
            this.aLabelSpeed.Name = "aLabelSpeed";
            this.aLabelSpeed.Size = new System.Drawing.Size(49, 17);
            this.aLabelSpeed.TabIndex = 9;
            this.aLabelSpeed.Text = "Speed";
            // 
            // aTextMicrocontroller
            // 
            this.aTextMicrocontroller.Location = new System.Drawing.Point(26, 32);
            this.aTextMicrocontroller.Multiline = true;
            this.aTextMicrocontroller.Name = "aTextMicrocontroller";
            this.aTextMicrocontroller.ReadOnly = true;
            this.aTextMicrocontroller.Size = new System.Drawing.Size(482, 403);
            this.aTextMicrocontroller.TabIndex = 13;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.aTextMicrocontroller);
            this.groupBox1.Location = new System.Drawing.Point(685, 24);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(535, 461);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Microcontroller Output";
            // 
            // aTimerMicrocontrollerOutput
            // 
            this.aTimerMicrocontrollerOutput.Enabled = true;
            this.aTimerMicrocontrollerOutput.Interval = 5000;
            this.aTimerMicrocontrollerOutput.Tick += new System.EventHandler(this.aTimerMicrocontrollerOutput_Tick);
            // 
            // aTimerContractButtonDown
            // 
            this.aTimerContractButtonDown.Tick += new System.EventHandler(this.aTimerContractButtonDown_Tick);
            // 
            // aTimerExtendButtonDown
            // 
            this.aTimerExtendButtonDown.Tick += new System.EventHandler(this.aTimerExtendButtonDown_Tick);
            // 
            // aHandControllerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.ClientSize = new System.Drawing.Size(1232, 527);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.aGroupControls);
            this.Controls.Add(this.aGroupConnection);
            this.Controls.Add(this.aTextOutput);
            this.Name = "aHandControllerForm";
            this.Text = "Hand Controller";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.aHandControllerForm_FormClosing);
            this.Load += new System.EventHandler(this.aHandControllerForm_Load);
            this.aGroupConnection.ResumeLayout(false);
            this.aGroupConnection.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.aTrackBarSpeed)).EndInit();
            this.aGroupControls.ResumeLayout(false);
            this.aGroupControls.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ListBox aListPortNames;
        private System.Windows.Forms.Button aButtonConnect;
        private System.Windows.Forms.ListBox aListBaudRates;
        private System.Windows.Forms.TextBox aTextOutput;
        private System.Windows.Forms.Label aLabelPortName;
        private System.Windows.Forms.Label aLabelBaudRate;
        private System.Windows.Forms.GroupBox aGroupConnection;
        private System.Windows.Forms.TrackBar aTrackBarSpeed;
        private System.Windows.Forms.GroupBox aGroupControls;
        private System.Windows.Forms.Label aLabelSpeed;
        private System.Windows.Forms.Button aButtonExtend;
        private System.Windows.Forms.Button aButtonContract;
        private System.Windows.Forms.Button aButtonStop;
        private System.Windows.Forms.Button aRefreshButton;
        private System.Windows.Forms.Button aButtonDisconnect;
        private System.Windows.Forms.TextBox aTextMicrocontroller;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Timer aTimerMicrocontrollerOutput;
        private System.Windows.Forms.Label aLabelSpeedValue;
        private System.Windows.Forms.Label aLabelSetCharBufferTimeout;
        private System.Windows.Forms.Button aButtonSetCharBufferTimeout;
        private System.Windows.Forms.TextBox aTextboxSetCharBufferTimeout;
        private System.Windows.Forms.Label aLabelSetCommandTimer;
        private System.Windows.Forms.Button aButtonSetCommandTimer;
        private System.Windows.Forms.TextBox aTextboxSetCommandTimer;
        private System.Windows.Forms.Timer aTimerContractButtonDown;
        private System.Windows.Forms.Timer aTimerExtendButtonDown;
    }
}

