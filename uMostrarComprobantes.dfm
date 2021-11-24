object fMostrarComprobantes: TfMostrarComprobantes
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Comprobantes cargados'
  ClientHeight = 681
  ClientWidth = 1261
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 613
    Width = 70
    Height = 13
    Caption = 'Nuevo per'#237'odo'
  end
  object Label2: TLabel
    Left = 16
    Top = 584
    Width = 398
    Height = 13
    Caption = 
      'Ingrese el nuevo per'#237'odo y luego haga doble click sobre el compr' +
      'obante a modificar'
  end
  object Button1: TButton
    Left = 208
    Top = 530
    Width = 210
    Height = 25
    Caption = 'Modificar este comprobante'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 752
    Top = 530
    Width = 210
    Height = 25
    Caption = 'Salir'
    TabOrder = 1
    OnClick = Button2Click
  end
  object DBG1: TDBGrid
    Left = 0
    Top = 3
    Width = 1260
    Height = 521
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = DBG1DblClick
    Columns = <
      item
        Expanded = False
        FieldName = 'fechaComprobante'
        Title.Alignment = taCenter
        Title.Caption = 'Fecha'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 83
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'proveedor'
        Title.Alignment = taCenter
        Title.Caption = 'Proveedor'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 161
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'ptoVenta'
        Title.Alignment = taCenter
        Title.Caption = 'P. Venta'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 57
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
        Width = 72
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'desDocumento'
        Title.Alignment = taCenter
        Title.Caption = 'Doc.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 89
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
        Width = 34
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'desCuentaCompra'
        Title.Alignment = taCenter
        Title.Caption = 'Cuenta'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 185
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'desJurisdiccion'
        Title.Alignment = taCenter
        Title.Caption = 'Jurisdicci'#243'n'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 95
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'netoGravado1'
        Title.Alignment = taCenter
        Title.Caption = 'NG 21%'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 75
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'netoGravado2'
        Title.Alignment = taCenter
        Title.Caption = 'NG 10,5%'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 93
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'netoGravado3'
        Title.Alignment = taCenter
        Title.Caption = 'NG 27%'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 78
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'retencionesIVA'
        Title.Alignment = taCenter
        Title.Caption = 'Ret. IVA'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 58
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'totIVA'
        Title.Alignment = taCenter
        Title.Caption = 'IVA Total'
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
        FieldName = 'percepcionesIVA'
        Title.Alignment = taCenter
        Title.Caption = 'Perc. IVA'
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
        FieldName = 'retencionesIB'
        Title.Alignment = taCenter
        Title.Caption = 'Ret. IB'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 60
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'percepcionesIB'
        Title.Alignment = taCenter
        Title.Caption = 'Perc. IB'
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
        FieldName = 'retencionesGanancias'
        Title.Alignment = taCenter
        Title.Caption = 'Ret. Gananc.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 85
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'conceptosNoGravados'
        Title.Alignment = taCenter
        Title.Caption = 'C. N. Grav.'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 65
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'exentos'
        Title.Alignment = taCenter
        Title.Caption = 'Exentos'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Visible = True
      end
      item
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
  object Button3: TButton
    Left = 528
    Top = 530
    Width = 105
    Height = 25
    Caption = 'Modificar per'#237'odo'
    TabOrder = 3
    OnClick = Button3Click
  end
  object EdPeriodo: TEdit
    Left = 92
    Top = 610
    Width = 48
    Height = 21
    MaxLength = 7
    NumbersOnly = True
    ParentShowHint = False
    ShowHint = False
    TabOrder = 4
    Text = '__/____'
    OnExit = EdPeriodoExit
    OnKeyDown = EdPeriodoKeyDown
    OnKeyPress = EdPeriodoKeyPress
    OnKeyUp = EdPeriodoKeyUp
    OnMouseUp = EdPeriodoMouseUp
  end
  object Button4: TButton
    Left = 16
    Top = 651
    Width = 75
    Height = 25
    Caption = 'Finalizar'
    TabOrder = 5
    OnClick = Button4Click
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 1193
    Top = 121
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
    Left = 1193
    Top = 177
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 1193
    Top = 225
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 1193
    Top = 273
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 1193
    Top = 329
    object CDSfechaComprobante: TDateField
      FieldName = 'fechaComprobante'
    end
    object CDSptoVenta: TIntegerField
      FieldName = 'ptoVenta'
      DisplayFormat = '00000'
    end
    object CDSnroComprobante: TIntegerField
      FieldName = 'nroComprobante'
      DisplayFormat = '00000000'
    end
    object CDSproveedor: TWideStringField
      FieldName = 'proveedor'
    end
    object CDSnetoGravado1: TFMTBCDField
      FieldName = 'netoGravado1'
      DisplayFormat = '$ 0.00'
    end
    object CDSnetoGravado2: TFMTBCDField
      FieldName = 'netoGravado2'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSnetoGravado3: TFMTBCDField
      FieldName = 'netoGravado3'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSretencionesIVA: TFMTBCDField
      FieldName = 'retencionesIVA'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSpercepcionesIVA: TFMTBCDField
      FieldName = 'percepcionesIVA'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSretencionesIB: TFMTBCDField
      FieldName = 'retencionesIB'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSpercepcionesIB: TFMTBCDField
      FieldName = 'percepcionesIB'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSretencionesGanancias: TFMTBCDField
      FieldName = 'retencionesGanancias'
      DisplayFormat = '$ 0.00'
    end
    object CDSconceptosNoGravados: TFMTBCDField
      FieldName = 'conceptosNoGravados'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSexentos: TFMTBCDField
      FieldName = 'exentos'
      DisplayFormat = '$ 0.00'
      Size = 0
    end
    object CDSdesTipo: TWideStringField
      FieldName = 'desTipo'
      Size = 0
    end
    object CDSdesDocumento: TWideStringField
      FieldName = 'desDocumento'
    end
    object CDSdesCuentaCompra: TWideStringField
      FieldName = 'desCuentaCompra'
      Size = 0
    end
    object CDSdesJurisdiccion: TWideStringField
      FieldName = 'desJurisdiccion'
      Size = 0
    end
    object CDSidTipo: TIntegerField
      FieldName = 'idTipo'
    end
    object CDSidDocumento: TIntegerField
      FieldName = 'idDocumento'
    end
    object CDScuit: TWideStringField
      FieldName = 'cuit'
    end
    object CDStotal: TFMTBCDField
      FieldName = 'total'
      DisplayFormat = '$ 0.00'
    end
    object CDSidComprobanteCompra: TIntegerField
      FieldName = 'idComprobanteCompra'
    end
    object CDStotIVA: TFMTBCDField
      FieldName = 'totIVA'
      DisplayFormat = '$ 0.00'
    end
  end
  object DataSource1: TDataSource
    AutoEdit = False
    DataSet = CDS
    Left = 1193
    Top = 385
  end
end
