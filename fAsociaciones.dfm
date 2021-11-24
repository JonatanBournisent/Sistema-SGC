object Asociaciones: TAsociaciones
  Left = 0
  Top = 0
  Caption = 'Asociaci'#243'n de cuentas'
  ClientHeight = 367
  ClientWidth = 393
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel3: TBevel
    Left = 17
    Top = 259
    Width = 360
    Height = 60
    Shape = bsFrame
  end
  object Bevel2: TBevel
    Left = 17
    Top = 189
    Width = 360
    Height = 60
    Shape = bsFrame
  end
  object Bevel1: TBevel
    Left = 17
    Top = 119
    Width = 360
    Height = 60
    Shape = bsFrame
  end
  object desContribuyente: TLabel
    Left = 125
    Top = 151
    Width = 4
    Height = 13
    Caption = '-'
  end
  object desAsociado: TLabel
    Left = 125
    Top = 222
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label2: TLabel
    Left = 26
    Top = 131
    Width = 111
    Height = 13
    Caption = 'CUIT del contribuyente'
  end
  object Label5: TLabel
    Left = 26
    Top = 201
    Width = 75
    Height = 13
    Caption = 'CUIT del cliente'
  end
  object Label7: TLabel
    Left = 26
    Top = 271
    Width = 111
    Height = 13
    Caption = 'Cuenta venta asociada'
  end
  object desCuenta: TLabel
    Left = 72
    Top = 291
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Bevel4: TBevel
    Left = 8
    Top = 8
    Width = 377
    Height = 352
  end
  object EdContribuyente: TEdit
    Left = 26
    Top = 149
    Width = 87
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 0
    Text = '__-________-_'
    OnExit = EdContribuyenteExit
    OnKeyDown = EdContribuyenteKeyDown
    OnKeyPress = EdContribuyenteKeyPress
    OnKeyUp = EdContribuyenteKeyUp
    OnMouseUp = EdContribuyenteMouseUp
  end
  object EdAsociado: TEdit
    Left = 26
    Top = 219
    Width = 87
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 1
    Text = '__-________-_'
    OnExit = EdAsociadoExit
    OnKeyDown = EdAsociadoKeyDown
    OnKeyPress = EdAsociadoKeyPress
    OnKeyUp = EdAsociadoKeyUp
    OnMouseUp = EdAsociadoMouseUp
  end
  object EdCuenta: TEdit
    Left = 26
    Top = 289
    Width = 33
    Height = 21
    NumbersOnly = True
    ParentShowHint = False
    ShowHint = False
    TabOrder = 2
    OnExit = EdCuentaExit
    OnKeyPress = EdCuentaKeyPress
  end
  object BtnGuardar: TButton
    Left = 58
    Top = 325
    Width = 121
    Height = 25
    Caption = 'Guardar'
    TabOrder = 3
    OnClick = BtnGuardarClick
  end
  object BtnCancelar: TButton
    Left = 216
    Top = 325
    Width = 121
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 4
    OnClick = BtnCancelarClick
  end
  object RG: TRadioGroup
    Left = 17
    Top = 16
    Width = 161
    Height = 89
    Caption = 'Tipo de cuenta'
    ItemIndex = 0
    Items.Strings = (
      'Cuentas ventas'
      'Cuentas compras')
    TabOrder = 5
    OnClick = RGClick
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 528
    Top = 32
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
    Left = 528
    Top = 104
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 672
    Top = 48
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 664
    Top = 120
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 552
    Top = 176
  end
end
