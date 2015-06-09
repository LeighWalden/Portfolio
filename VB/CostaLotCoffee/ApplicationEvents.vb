Namespace My
    ' The following events are available for MyApplication:
    ' 
    ' Startup: Raised when the application starts, before the startup form is created.
    ' Shutdown: Raised after all application forms are closed.  This event is not raised if the application terminates abnormally.
    ' UnhandledException: Raised if the application encounters an unhandled exception.
    ' StartupNextInstance: Raised when launching a single-instance application and the application is already active. 
    ' NetworkAvailabilityChanged: Raised when the network connection is connected or disconnected.
    Partial Friend Class MyApplication
        'from http://msdn.microsoft.com/en-us/library/microsoft.visualbasic.applicationservices.windowsformsapplicationbase.minimumsplashscreendisplaytime.aspx#Y0
        'OnInitialize is a preset of instructions that sets the styles of the current program this delays this till after the splash screen
        Protected Overrides Function OnInitialize(
          ByVal commandLineArgs As System.Collections.
              ObjectModel.ReadOnlyCollection(Of String)
      ) As Boolean
            ' Set the display time to 5000 milliseconds (5 seconds). 
            Me.MinimumSplashScreenDisplayTime = 5000 'Displays the splash screen for 5 seconds
            Return MyBase.OnInitialize(commandLineArgs) 'OnInitialize is then called in
        End Function
    End Class


End Namespace
