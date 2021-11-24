object AgregarContribuyente: TAgregarContribuyente
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Agergar'
  ClientHeight = 306
  ClientWidth = 426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 27
    Width = 24
    Height = 13
    Caption = 'CUIT'
  end
  object Label2: TLabel
    Left = 24
    Top = 67
    Width = 59
    Height = 13
    Caption = 'Raz'#243'n social'
  end
  object Label3: TLabel
    Left = 24
    Top = 107
    Width = 108
    Height = 13
    Caption = 'Condicion frente a IVA'
  end
  object Label4: TLabel
    Left = 24
    Top = 147
    Width = 54
    Height = 13
    Caption = 'Jurisdicci'#243'n'
  end
  object Label5: TLabel
    Left = 24
    Top = 227
    Width = 86
    Height = 13
    Caption = 'Es contribuyente?'
  end
  object desCondIVA: TLabel
    Left = 222
    Top = 107
    Width = 4
    Height = 13
    Caption = '-'
  end
  object desJurisdiccion: TLabel
    Left = 222
    Top = 147
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label7: TLabel
    Left = 24
    Top = 187
    Width = 118
    Height = 13
    Caption = 'Cuenta compra asociada'
  end
  object desCuenta: TLabel
    Left = 222
    Top = 187
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 409
    Height = 249
  end
  object SpeedButton1: TSpeedButton
    Left = 150
    Top = 184
    Width = 20
    Height = 21
    Caption = '+'
    OnClick = SpeedButton1Click
  end
  object EdCUIT: TEdit
    Left = 176
    Top = 24
    Width = 85
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 0
    Text = '__-________-_'
    OnExit = EdCUITExit
    OnKeyDown = EdCUITKeyDown
    OnKeyPress = EdCUITKeyPress
    OnKeyUp = EdCUITKeyUp
  end
  object EdRazonSocial: TEdit
    Left = 176
    Top = 64
    Width = 233
    Height = 21
    MaxLength = 45
    TabOrder = 1
    OnExit = EdRazonSocialExit
  end
  object BtnGuardar: TButton
    Left = 50
    Top = 272
    Width = 142
    Height = 25
    Caption = 'Guardar datos'
    TabOrder = 6
    OnClick = BtnGuardarClick
  end
  object EdCondIVA: TEdit
    Left = 176
    Top = 104
    Width = 40
    Height = 21
    TabOrder = 2
    OnExit = EdCondIVAExit
    OnKeyPress = EdCondIVAKeyPress
  end
  object EdJurisdiccion: TEdit
    Left = 176
    Top = 144
    Width = 40
    Height = 21
    TabOrder = 3
    OnExit = EdJurisdiccionExit
    OnKeyPress = EdJurisdiccionKeyPress
  end
  object CBCliente: TComboBox
    Left = 176
    Top = 224
    Width = 40
    Height = 22
    Style = csOwnerDrawFixed
    ItemIndex = 0
    TabOrder = 5
    Text = 'NO'
    Items.Strings = (
      'NO'
      'SI')
  end
  object BtnCancelar: TButton
    Left = 235
    Top = 272
    Width = 142
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 7
    OnClick = BtnCancelarClick
  end
  object EdCuenta: TEdit
    Left = 176
    Top = 184
    Width = 40
    Height = 21
    TabOrder = 4
    OnExit = EdCuentaExit
    OnKeyPress = EdCuentaKeyPress
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 496
    Top = 72
  end
  object SQLConnection1: TSQLConnection
    ConnectionName = 'MySQLConnection'
    DriverName = 'MySQL'
    LoginPrompt = False
    Params.Strings = (
      'DriverName=MySQL'
      'HostName=localhost'
      'Database=sgc'
      'User_Name=sistemaContable'
      'Password=Rightround8'
      'ServerCharSet=utf8'
      'BlobSize=-1'
      'ErrorResourceFile='
      'LocaleCode=0000'
      'Compressed=False'
      'Encrypted=False'
      'ConnectTimeout=60')
    Left = 496
    Top = 144
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 640
    Top = 88
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 632
    Top = 160
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 520
    Top = 216
  end
end
