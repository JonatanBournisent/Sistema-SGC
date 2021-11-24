object Opciones: TOpciones
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Opciones'
  ClientHeight = 319
  ClientWidth = 360
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 64
    Top = 231
    Width = 238
    Height = 42
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 74
    Top = 245
    Width = 28
    Height = 13
    Caption = 'Filtrar'
  end
  object Bevel2: TBevel
    Left = 8
    Top = 8
    Width = 343
    Height = 273
  end
  object DBGrid1: TDBGrid
    Left = 16
    Top = 16
    Width = 327
    Height = 209
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'idCuentaCompra'
        Title.Alignment = taCenter
        Title.Caption = 'id'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 31
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'desCuentaCompra'
        Title.Alignment = taCenter
        Title.Caption = 'Descripci'#243'n'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 260
        Visible = True
      end>
  end
  object Edit1: TEdit
    Left = 108
    Top = 242
    Width = 183
    Height = 21
    TabOrder = 1
    OnChange = Edit1Change
  end
  object Button1: TButton
    Left = 108
    Top = 287
    Width = 137
    Height = 25
    Caption = 'Salir'
    TabOrder = 2
    OnClick = Button1Click
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
    Left = 392
    Top = 8
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 448
    Top = 16
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 520
    Top = 16
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 600
    Top = 32
  end
  object DataSource1: TDataSource
    AutoEdit = False
    DataSet = ClientDataSet1
    Left = 688
    Top = 32
  end
end
