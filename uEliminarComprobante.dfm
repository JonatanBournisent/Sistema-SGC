object EliminarComprobante: TEliminarComprobante
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Eliminar un Comprobante'
  ClientHeight = 592
  ClientWidth = 705
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
  object Bevel2: TBevel
    Left = 160
    Top = 136
    Width = 374
    Height = 50
  end
  object Bevel1: TBevel
    Left = 272
    Top = 407
    Width = 238
    Height = 42
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 282
    Top = 421
    Width = 28
    Height = 13
    Caption = 'Filtrar'
  end
  object Label2: TLabel
    Left = 169
    Top = 153
    Width = 69
    Height = 13
    Caption = 'Contribuyente'
  end
  object desContribuyente: TLabel
    Left = 335
    Top = 153
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label6: TLabel
    Left = 182
    Top = 234
    Width = 144
    Height = 13
    Caption = 'Pto. venta - Nro comprobante'
  end
  object Label3: TLabel
    Left = 378
    Top = 234
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label4: TLabel
    Left = 182
    Top = 270
    Width = 110
    Height = 13
    Caption = 'Fecha de comprobante'
  end
  object Label8: TLabel
    Left = 182
    Top = 300
    Width = 54
    Height = 13
    Caption = 'Documento'
  end
  object desDocumento: TLabel
    Left = 371
    Top = 300
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label9: TLabel
    Left = 182
    Top = 327
    Width = 20
    Height = 13
    Caption = 'Tipo'
  end
  object desTipo: TLabel
    Left = 371
    Top = 327
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label5: TLabel
    Left = 168
    Top = 128
    Width = 76
    Height = 13
    Caption = 'Dato obligatorio'
    Transparent = False
  end
  object Bevel3: TBevel
    Left = 160
    Top = 208
    Width = 374
    Height = 147
  end
  object Label7: TLabel
    Left = 168
    Top = 200
    Width = 82
    Height = 13
    Caption = 'Filtros opcionales'
    Transparent = False
  end
  object Bevel4: TBevel
    Left = 8
    Top = 8
    Width = 689
    Height = 545
  end
  object DBGrid1: TDBGrid
    Left = 24
    Top = 407
    Width = 657
    Height = 130
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
        Expanded = False
        FieldName = 'fechaComprobante'
        Title.Alignment = taCenter
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 213
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'ptoVenta'
        Title.Alignment = taCenter
        Title.Caption = 'Pto. Vta.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'nroComprobante'
        Title.Alignment = taCenter
        Title.Caption = 'Nro. Comp.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'desTipo'
        Title.Alignment = taCenter
        Title.Caption = 'Tipo'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 46
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'desDocumento'
        Title.Alignment = taCenter
        Title.Caption = 'Documento'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 87
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'total'
        Title.Alignment = taCenter
        Title.Caption = 'Total'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 74
        Visible = True
      end>
  end
  object Button1: TButton
    Left = 379
    Top = 559
    Width = 201
    Height = 25
    Caption = 'Salir'
    TabOrder = 1
    OnClick = Button1Click
  end
  object EdContribuyente: TEdit
    Left = 244
    Top = 150
    Width = 85
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 2
    Text = '__-________-_'
    OnExit = EdContribuyenteExit
    OnKeyDown = EdContribuyenteKeyDown
    OnKeyPress = EdContribuyenteKeyPress
    OnKeyUp = EdContribuyenteKeyUp
    OnMouseUp = EdContribuyenteMouseUp
  end
  object EdPtoVenta: TEdit
    Left = 332
    Top = 231
    Width = 40
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 3
    Text = '0000'
    OnExit = EdPtoVentaExit
    OnMouseUp = EdPtoVentaMouseUp
  end
  object EdNroComprobante: TEdit
    Left = 388
    Top = 231
    Width = 73
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 4
    Text = '00000000'
    OnExit = EdNroComprobanteExit
    OnMouseUp = EdNroComprobanteMouseUp
  end
  object EdFecha: TEdit
    Left = 332
    Top = 267
    Width = 65
    Height = 21
    NumbersOnly = True
    TabOrder = 5
    Text = '__/__/____'
    OnExit = EdFechaExit
    OnKeyDown = EdFechaKeyDown
    OnKeyPress = EdFechaKeyPress
    OnKeyUp = EdFechaKeyUp
  end
  object EdDocumento: TEdit
    Left = 332
    Top = 297
    Width = 33
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 6
    OnExit = EdDocumentoExit
    OnKeyPress = EdDocumentoKeyPress
    OnMouseUp = EdDocumentoMouseUp
  end
  object EdTipo: TEdit
    Left = 332
    Top = 324
    Width = 33
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 7
    OnExit = EdTipoExit
    OnKeyPress = EdTipoKeyPress
    OnMouseUp = EdTipoMouseUp
  end
  object RG1: TRadioGroup
    Left = 160
    Top = 16
    Width = 374
    Height = 105
    Caption = 'Comprobantes a examinar'
    ItemIndex = 0
    Items.Strings = (
      'Comprobantes de ventas'
      'Comprobantes de compras')
    TabOrder = 8
    OnClick = RG1Click
  end
  object Button2: TButton
    Left = 160
    Top = 361
    Width = 374
    Height = 25
    Caption = 'Filtrar'
    TabOrder = 9
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 125
    Top = 559
    Width = 201
    Height = 25
    Caption = 'Eliminar comprobante seleccionado'
    TabOrder = 10
    OnClick = Button3Click
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
    Left = 632
    Top = 40
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 688
    Top = 48
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 584
    Top = 104
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 664
    Top = 120
    object ClientDataSet1fechaComprobante: TDateField
      Alignment = taCenter
      DisplayLabel = 'Fecha'
      FieldName = 'fechaComprobante'
    end
    object ClientDataSet1cliente: TWideStringField
      FieldName = 'cliente'
    end
    object ClientDataSet1ptoVenta: TIntegerField
      FieldName = 'ptoVenta'
      DisplayFormat = '00000'
    end
    object ClientDataSet1nroComprobante: TIntegerField
      FieldName = 'nroComprobante'
      DisplayFormat = '00000000'
    end
    object ClientDataSet1desTipo: TWideStringField
      FieldName = 'desTipo'
    end
    object ClientDataSet1desDocumento: TWideStringField
      FieldName = 'desDocumento'
    end
    object ClientDataSet1total: TFMTBCDField
      FieldName = 'total'
      DisplayFormat = '$ 0.00'
    end
    object ClientDataSet1idComprobanteVenta: TIntegerField
      FieldName = 'idComprobanteVenta'
    end
  end
  object DataSource1: TDataSource
    AutoEdit = False
    DataSet = ClientDataSet1
    Left = 752
    Top = 120
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 592
    Top = 144
  end
end
