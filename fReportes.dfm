object Reportes: TReportes
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Reportes'
  ClientHeight = 643
  ClientWidth = 1002
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel16: TBevel
    Left = 8
    Top = 8
    Width = 987
    Height = 625
  end
  object Bevel19: TBevel
    Left = 23
    Top = 350
    Width = 274
    Height = 131
  end
  object Bevel15: TBevel
    Left = 23
    Top = 16
    Width = 954
    Height = 121
    Shape = bsFrame
  end
  object Bevel12: TBevel
    Left = 355
    Top = 350
    Width = 388
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel1: TBevel
    Left = 354
    Top = 373
    Width = 388
    Height = 20
    Shape = bsBottomLine
  end
  object Label2: TLabel
    Left = 355
    Top = 372
    Width = 40
    Height = 13
    Caption = 'NG 21%'
  end
  object Label3: TLabel
    Left = 355
    Top = 397
    Width = 50
    Height = 13
    Caption = 'NG 10,5%'
  end
  object Label4: TLabel
    Left = 355
    Top = 420
    Width = 40
    Height = 13
    Caption = 'NG 27%'
  end
  object Label5: TLabel
    Left = 684
    Top = 759
    Width = 88
    Height = 13
    Caption = 'Alicuota IVA 0.0%'
    Visible = False
  end
  object Label6: TLabel
    Left = 355
    Top = 443
    Width = 79
    Height = 13
    Caption = 'Retenciones IVA'
  end
  object Label7: TLabel
    Left = 355
    Top = 466
    Width = 83
    Height = 13
    Caption = 'Percepciones IVA'
  end
  object Label8: TLabel
    Left = 355
    Top = 489
    Width = 82
    Height = 13
    Caption = 'Retenciones IIBB'
  end
  object Label9: TLabel
    Left = 355
    Top = 512
    Width = 86
    Height = 13
    Caption = 'Percepciones IIBB'
  end
  object Label10: TLabel
    Left = 355
    Top = 535
    Width = 111
    Height = 13
    Caption = 'Retenciones Ganancias'
  end
  object Label11: TLabel
    Left = 355
    Top = 558
    Width = 114
    Height = 13
    Caption = 'Conceptos no gravados'
  end
  object Label12: TLabel
    Left = 355
    Top = 581
    Width = 39
    Height = 13
    Caption = 'Exentos'
  end
  object Label13: TLabel
    Left = 39
    Top = 383
    Width = 49
    Height = 19
    Caption = 'Total:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label14: TLabel
    Left = 515
    Top = 372
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label15: TLabel
    Left = 515
    Top = 395
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label16: TLabel
    Left = 515
    Top = 418
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label17: TLabel
    Left = 844
    Top = 759
    Width = 4
    Height = 13
    Caption = '-'
    Visible = False
  end
  object Label18: TLabel
    Left = 515
    Top = 441
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label19: TLabel
    Left = 515
    Top = 464
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label20: TLabel
    Left = 515
    Top = 487
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label21: TLabel
    Left = 515
    Top = 510
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label22: TLabel
    Left = 515
    Top = 533
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label23: TLabel
    Left = 515
    Top = 556
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label24: TLabel
    Left = 515
    Top = 579
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label25: TLabel
    Left = 138
    Top = 383
    Width = 7
    Height = 19
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object desContribuyente: TLabel
    Left = 35
    Top = 55
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label26: TLabel
    Left = 627
    Top = 372
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label27: TLabel
    Left = 627
    Top = 395
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label28: TLabel
    Left = 627
    Top = 418
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label29: TLabel
    Left = 956
    Top = 759
    Width = 4
    Height = 13
    Caption = '-'
    Visible = False
  end
  object Label30: TLabel
    Left = 514
    Top = 348
    Width = 63
    Height = 18
    Caption = 'Subtotal'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label31: TLabel
    Left = 354
    Top = 348
    Width = 69
    Height = 18
    Caption = 'Concepto'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label32: TLabel
    Left = 627
    Top = 348
    Width = 94
    Height = 18
    Caption = 'Subtotal IVA'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel2: TBevel
    Left = 354
    Top = 396
    Width = 388
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel3: TBevel
    Left = 355
    Top = 419
    Width = 388
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel4: TBevel
    Left = 683
    Top = 752
    Width = 388
    Height = 26
    Shape = bsBottomLine
    Visible = False
  end
  object Bevel5: TBevel
    Left = 355
    Top = 442
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel6: TBevel
    Left = 355
    Top = 465
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel7: TBevel
    Left = 354
    Top = 488
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel8: TBevel
    Left = 355
    Top = 511
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel9: TBevel
    Left = 355
    Top = 534
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel10: TBevel
    Left = 354
    Top = 557
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel11: TBevel
    Left = 354
    Top = 580
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object Bevel13: TBevel
    Left = 506
    Top = 349
    Width = 25
    Height = 272
    Shape = bsLeftLine
  end
  object Bevel14: TBevel
    Left = 620
    Top = 349
    Width = 25
    Height = 88
    Shape = bsLeftLine
  end
  object Label33: TLabel
    Left = 35
    Top = 30
    Width = 111
    Height = 13
    Caption = 'CUIT del contribuyente'
  end
  object Label34: TLabel
    Left = 35
    Top = 94
    Width = 112
    Height = 13
    Caption = 'Per'#237'odo de observaci'#243'n'
  end
  object Label35: TLabel
    Left = 475
    Top = 80
    Width = 83
    Height = 13
    Caption = 'Cuenta analizada'
  end
  object Label36: TLabel
    Left = 475
    Top = 30
    Width = 102
    Height = 13
    Caption = 'Jurisdicci'#243'n analizada'
  end
  object Bevel17: TBevel
    Left = 315
    Top = 349
    Width = 17
    Height = 272
    Shape = bsLeftLine
  end
  object Label38: TLabel
    Left = 666
    Top = 30
    Width = 37
    Height = 13
    Caption = 'Cliente:'
  end
  object desProCli: TLabel
    Left = 635
    Top = 76
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label1: TLabel
    Left = 39
    Top = 433
    Width = 84
    Height = 19
    Caption = 'Total IVA:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label37: TLabel
    Left = 138
    Top = 433
    Width = 7
    Height = 19
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Bevel18: TBevel
    Left = 23
    Top = 499
    Width = 274
    Height = 118
  end
  object Label39: TLabel
    Left = 355
    Top = 604
    Width = 105
    Height = 13
    Caption = 'Compras no inscriptas'
  end
  object Label40: TLabel
    Left = 515
    Top = 604
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Bevel20: TBevel
    Left = 355
    Top = 603
    Width = 266
    Height = 20
    Shape = bsBottomLine
  end
  object DBG1: TDBGrid
    Left = 23
    Top = 143
    Width = 954
    Height = 194
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
        Width = 87
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
        Title.Caption = 'Ret. IIBB'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clWindowText
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = [fsBold]
        Width = 61
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'percepcionesIB'
        Title.Alignment = taCenter
        Title.Caption = 'Perc. IIBB'
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
  object EdContribuyente: TEdit
    Left = 184
    Top = 27
    Width = 89
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 2
    Text = '__-________-_'
    OnExit = EdContribuyenteExit
    OnKeyDown = EdContribuyenteKeyDown
    OnKeyPress = EdContribuyenteKeyPress
    OnKeyUp = EdContribuyenteKeyUp
    OnMouseDown = EdContribuyenteMouseDown
    OnMouseUp = EdContribuyenteMouseUp
  end
  object EdPeriodo: TEdit
    Left = 153
    Top = 91
    Width = 56
    Height = 21
    MaxLength = 7
    NumbersOnly = True
    ParentShowHint = False
    ShowHint = False
    TabOrder = 3
    Text = '__/____'
    OnExit = EdPeriodoExit
    OnKeyDown = EdPeriodoKeyDown
    OnKeyPress = EdPeriodoKeyPress
    OnKeyUp = EdPeriodoKeyUp
    OnMouseUp = EdPeriodoMouseUp
  end
  object RG1: TRadioGroup
    Left = 315
    Top = 27
    Width = 137
    Height = 102
    Caption = 'Opciones'
    ItemIndex = 0
    Items.Strings = (
      'Libro IVA ventas'
      'Libro IVA compras')
    TabOrder = 4
    OnClick = RG1Click
  end
  object CB1: TComboBox
    Left = 475
    Top = 45
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 5
    OnChange = CB1Change
  end
  object CB2: TComboBox
    Left = 475
    Top = 95
    Width = 145
    Height = 21
    Style = csDropDownList
    Enabled = False
    TabOrder = 6
    OnChange = CB2Change
  end
  object EdProCli: TEdit
    Left = 666
    Top = 45
    Width = 89
    Height = 21
    Enabled = False
    TabOrder = 8
    Text = '__-________-_'
    OnExit = EdProCliExit
    OnKeyDown = EdProCliKeyDown
    OnKeyPress = EdProCliKeyPress
    OnKeyUp = EdProCliKeyUp
    OnMouseUp = EdProCliMouseUp
  end
  object Button3: TButton
    Left = 58
    Top = 512
    Width = 206
    Height = 25
    Caption = 'Generar Reg. Inf. Ventas'
    TabOrder = 9
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 57
    Top = 545
    Width = 206
    Height = 25
    Caption = 'Generar Reg. Inf. compras'
    Enabled = False
    TabOrder = 10
    OnClick = Button4Click
  end
  object CkB1: TCheckBox
    Left = 855
    Top = 22
    Width = 113
    Height = 17
    Caption = 'Retenci'#243'n IVA'
    TabOrder = 11
    OnClick = CkB1Click
  end
  object CkB2: TCheckBox
    Left = 855
    Top = 45
    Width = 113
    Height = 17
    Caption = 'Percepci'#243'n IVA'
    TabOrder = 12
    OnClick = CkB2Click
  end
  object CkB3: TCheckBox
    Left = 855
    Top = 68
    Width = 113
    Height = 17
    Caption = 'Retenci'#243'n IIBB'
    TabOrder = 13
    OnClick = CkB3Click
  end
  object CkB4: TCheckBox
    Left = 855
    Top = 91
    Width = 113
    Height = 17
    Caption = 'Percepci'#243'n IIBB'
    TabOrder = 14
    OnClick = CkB4Click
  end
  object CkB5: TCheckBox
    Left = 855
    Top = 113
    Width = 113
    Height = 17
    Caption = 'Retencion Gcias'
    TabOrder = 15
    OnClick = CkB5Click
  end
  object Button2: TButton
    Left = 58
    Top = 583
    Width = 206
    Height = 25
    Caption = 'Exportar reporte'
    TabOrder = 16
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 152
    Top = 27
    Width = 26
    Height = 21
    TabOrder = 1
    OnExit = Edit1Exit
  end
  object Edit2: TEdit
    Left = 635
    Top = 45
    Width = 25
    Height = 21
    TabOrder = 7
    OnExit = Edit2Exit
  end
  object UpDown1: TUpDown
    Left = 210
    Top = 91
    Width = 17
    Height = 21
    Min = -10000
    Max = 10000
    TabOrder = 17
    OnClick = UpDown1Click
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
    Left = 1208
    Top = 312
  end
  object Query1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 1208
    Top = 360
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = Query1
    Left = 1208
    Top = 408
  end
  object CDS: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 1208
    Top = 464
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
    object CDStotIVA: TFMTBCDField
      FieldName = 'totIVA'
      DisplayFormat = '$ 0.00'
    end
  end
  object DataSource1: TDataSource
    AutoEdit = False
    DataSet = CDS
    Left = 1208
    Top = 520
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 1208
    Top = 256
  end
  object SaveDialog1: TSaveDialog
    Left = 800
    Top = 65528
  end
end
