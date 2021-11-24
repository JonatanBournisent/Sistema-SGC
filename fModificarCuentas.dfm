object ModificarCuentas: TModificarCuentas
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Modificar Cuentas'
  ClientHeight = 399
  ClientWidth = 361
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 345
    Height = 353
  end
  object DBGrid1: TDBGrid
    Left = 16
    Top = 127
    Width = 329
    Height = 187
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'idCuentaVenta'
        Title.Alignment = taCenter
        Title.Caption = 'ID'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 50
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'desCuentaVenta'
        Title.Alignment = taCenter
        Title.Caption = 'Cuenta'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 238
        Visible = True
      end>
  end
  object RG: TRadioGroup
    Left = 16
    Top = 16
    Width = 185
    Height = 105
    Caption = 'Tipo de cuenta'
    ItemIndex = 0
    Items.Strings = (
      'Cuentas ventas'
      'Cuentas compras')
    TabOrder = 1
    OnClick = RGClick
  end
  object Button1: TButton
    Left = 16
    Top = 367
    Width = 145
    Height = 25
    Caption = 'Modificar cuenta'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 200
    Top = 367
    Width = 145
    Height = 25
    Caption = 'Agregar cuenta'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 16
    Top = 328
    Width = 329
    Height = 21
    TabOrder = 4
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
    Left = 484
    Top = 40
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 484
    Top = 104
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 588
    Top = 96
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 544
    Top = 288
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 504
    Top = 384
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 464
    Top = 264
  end
end
