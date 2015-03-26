Public Class CmdCalc
    Dim Month(11) As Double 'Array variable

    Private Sub CmdQuit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdQuit.Click
        Dim intResponse As Integer 'quits the application
        intResponse = MsgBox("Do you really want to exit this application?", 276, "Exit?")
        End
    End Sub

    Private Sub CmdEnter_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdAdd.Click
        Dim Value As Integer
        For Value = 0 To 11
            Month(Value) += InputBox("Enter mothly coffee usage in kilos  ") 'Brings up a 12 boxes one after the other so the user can input monthly data
        Next
    End Sub
    Private Sub CmdDisplay_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdDisplay.Click
        Dim Display As Integer
        For Display = 0 To 11
            LbDisplay.Items.Add(Month(Display))
            ' this lists the content of each element and displays them
        Next

    End Sub

    Private Sub CmdClear_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdClear.Click
        LbDisplay.Items.Clear() 'clears the display in the list box
        Dim index As Integer 'sets the array values back to 0
        For index = 0 To 11
            Month(index) = 0
        Next

    End Sub
    Private Sub CmdTotal_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdTotal.Click
        Dim total As Single ' a variable to keep the total wieghts
        Dim number As Integer
        Dim average As Single ' a variable to store the average sales
        total = 0
        number = 12
        For index = 0 To 11
            total = total + Month(index)
        Next
        LblTotal.Text = total
        average = (total / number)
        LblAverage.Text = average



    End Sub

    Private Sub CmdAscend_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdAscend.Click
        LbDisplay.Items.Clear() 'clears the display in the list box
        Dim Asc As Integer ' displays the array values in ascending order
        Array.Sort(Month)
        For Asc = 0 To 11
            LbDisplay.Items.Add(Month(Asc))
        Next

    End Sub

    Private Sub CmdDescend_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CmdDescend.Click
        LbDisplay.Items.Clear() 'clears the display in the list box
        Dim Desc As Integer ' displays the array values in descending order
        Array.Reverse(Month)
        For Desc = 0 To 11
            LbDisplay.Items.Add(Month(Desc))

        Next
    End Sub
End Class
