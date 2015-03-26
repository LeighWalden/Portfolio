<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class CmdCalc
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.CmdQuit = New System.Windows.Forms.Button()
        Me.CmdAscend = New System.Windows.Forms.Button()
        Me.CmdDescend = New System.Windows.Forms.Button()
        Me.LbDisplay = New System.Windows.Forms.ListBox()
        Me.CmdTotal = New System.Windows.Forms.Button()
        Me.CmdAdd = New System.Windows.Forms.Button()
        Me.CmdDisplay = New System.Windows.Forms.Button()
        Me.CmdClear = New System.Windows.Forms.Button()
        Me.LblTotal = New System.Windows.Forms.Label()
        Me.LblAverage = New System.Windows.Forms.Label()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.GroupBox3 = New System.Windows.Forms.GroupBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.SuspendLayout()
        '
        'CmdQuit
        '
        Me.CmdQuit.Location = New System.Drawing.Point(302, 357)
        Me.CmdQuit.Name = "CmdQuit"
        Me.CmdQuit.Size = New System.Drawing.Size(75, 23)
        Me.CmdQuit.TabIndex = 0
        Me.CmdQuit.Text = "Quit"
        Me.CmdQuit.UseVisualStyleBackColor = True
        '
        'CmdAscend
        '
        Me.CmdAscend.Location = New System.Drawing.Point(6, 36)
        Me.CmdAscend.Name = "CmdAscend"
        Me.CmdAscend.Size = New System.Drawing.Size(75, 23)
        Me.CmdAscend.TabIndex = 1
        Me.CmdAscend.Text = "Ascending"
        Me.CmdAscend.UseVisualStyleBackColor = True
        '
        'CmdDescend
        '
        Me.CmdDescend.Location = New System.Drawing.Point(87, 36)
        Me.CmdDescend.Name = "CmdDescend"
        Me.CmdDescend.Size = New System.Drawing.Size(75, 23)
        Me.CmdDescend.TabIndex = 2
        Me.CmdDescend.Text = "Descending"
        Me.CmdDescend.UseVisualStyleBackColor = True
        '
        'LbDisplay
        '
        Me.LbDisplay.FormattingEnabled = True
        Me.LbDisplay.Location = New System.Drawing.Point(12, 12)
        Me.LbDisplay.Name = "LbDisplay"
        Me.LbDisplay.Size = New System.Drawing.Size(281, 368)
        Me.LbDisplay.TabIndex = 3
        '
        'CmdTotal
        '
        Me.CmdTotal.Location = New System.Drawing.Point(6, 31)
        Me.CmdTotal.Name = "CmdTotal"
        Me.CmdTotal.Size = New System.Drawing.Size(75, 23)
        Me.CmdTotal.TabIndex = 4
        Me.CmdTotal.Text = "Calulate"
        Me.CmdTotal.UseVisualStyleBackColor = True
        '
        'CmdAdd
        '
        Me.CmdAdd.Location = New System.Drawing.Point(6, 29)
        Me.CmdAdd.Name = "CmdAdd"
        Me.CmdAdd.Size = New System.Drawing.Size(75, 23)
        Me.CmdAdd.TabIndex = 7
        Me.CmdAdd.Text = "Add Values"
        Me.CmdAdd.UseVisualStyleBackColor = True
        '
        'CmdDisplay
        '
        Me.CmdDisplay.Location = New System.Drawing.Point(87, 30)
        Me.CmdDisplay.Name = "CmdDisplay"
        Me.CmdDisplay.Size = New System.Drawing.Size(75, 51)
        Me.CmdDisplay.TabIndex = 8
        Me.CmdDisplay.Text = "Display Content"
        Me.CmdDisplay.UseVisualStyleBackColor = True
        '
        'CmdClear
        '
        Me.CmdClear.Location = New System.Drawing.Point(477, 81)
        Me.CmdClear.Name = "CmdClear"
        Me.CmdClear.Size = New System.Drawing.Size(75, 23)
        Me.CmdClear.TabIndex = 9
        Me.CmdClear.Text = "Clear"
        Me.CmdClear.UseVisualStyleBackColor = True
        '
        'LblTotal
        '
        Me.LblTotal.AutoSize = True
        Me.LblTotal.Location = New System.Drawing.Point(87, 60)
        Me.LblTotal.Name = "LblTotal"
        Me.LblTotal.Size = New System.Drawing.Size(0, 13)
        Me.LblTotal.TabIndex = 10
        '
        'LblAverage
        '
        Me.LblAverage.AutoSize = True
        Me.LblAverage.Location = New System.Drawing.Point(153, 60)
        Me.LblAverage.Name = "LblAverage"
        Me.LblAverage.Size = New System.Drawing.Size(0, 13)
        Me.LblAverage.TabIndex = 11
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.CmdAdd)
        Me.GroupBox1.Controls.Add(Me.CmdDisplay)
        Me.GroupBox1.Location = New System.Drawing.Point(302, 51)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(260, 91)
        Me.GroupBox1.TabIndex = 12
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Amending display"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label2)
        Me.GroupBox2.Controls.Add(Me.LblAverage)
        Me.GroupBox2.Controls.Add(Me.Label1)
        Me.GroupBox2.Controls.Add(Me.LblTotal)
        Me.GroupBox2.Controls.Add(Me.CmdTotal)
        Me.GroupBox2.Location = New System.Drawing.Point(302, 148)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(260, 94)
        Me.GroupBox2.TabIndex = 13
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Calculations of the data"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(153, 36)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(47, 13)
        Me.Label2.TabIndex = 14
        Me.Label2.Text = "Average"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(87, 36)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(31, 13)
        Me.Label1.TabIndex = 5
        Me.Label1.Text = "Total"
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.CmdAscend)
        Me.GroupBox3.Controls.Add(Me.CmdDescend)
        Me.GroupBox3.Location = New System.Drawing.Point(302, 249)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(170, 71)
        Me.GroupBox3.TabIndex = 14
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Sort data"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(299, 12)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(262, 26)
        Me.Label3.TabIndex = 15
        Me.Label3.Text = "All data should be entered in kilos as all outputs will be" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "displayed as kilos"
        '
        'CmdCalc
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(572, 396)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.CmdClear)
        Me.Controls.Add(Me.LbDisplay)
        Me.Controls.Add(Me.CmdQuit)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.GroupBox3)
        Me.Name = "CmdCalc"
        Me.Text = "Form1"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.GroupBox3.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents CmdQuit As System.Windows.Forms.Button
    Friend WithEvents CmdAscend As System.Windows.Forms.Button
    Friend WithEvents CmdDescend As System.Windows.Forms.Button
    Friend WithEvents LbDisplay As System.Windows.Forms.ListBox
    Friend WithEvents CmdTotal As System.Windows.Forms.Button
    Friend WithEvents CmdAdd As System.Windows.Forms.Button
    Friend WithEvents CmdDisplay As System.Windows.Forms.Button
    Friend WithEvents CmdClear As System.Windows.Forms.Button
    Friend WithEvents LblTotal As System.Windows.Forms.Label
    Friend WithEvents LblAverage As System.Windows.Forms.Label
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents Label3 As System.Windows.Forms.Label

End Class
