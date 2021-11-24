object CargarVentas: TCargarVentas
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Cargar comprobante de venta'
  ClientHeight = 530
  ClientWidth = 721
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
  object Bevel5: TBevel
    Left = 8
    Top = 8
    Width = 705
    Height = 473
  end
  object Label21: TLabel
    Left = 363
    Top = 413
    Width = 36
    Height = 13
    Caption = 'TOTAL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label20: TLabel
    Left = 26
    Top = 453
    Width = 34
    Height = 13
    Caption = 'Exento'
  end
  object Label19: TLabel
    Left = 24
    Top = 416
    Width = 105
    Height = 13
    Caption = 'Concepto no Gravado'
  end
  object Label18: TLabel
    Left = 363
    Top = 372
    Width = 100
    Height = 13
    Caption = 'Retenci'#243'n Ganancias'
  end
  object Label17: TLabel
    Left = 363
    Top = 345
    Width = 75
    Height = 13
    Caption = 'Percepci'#243'n IIBB'
  end
  object Label16: TLabel
    Left = 363
    Top = 318
    Width = 71
    Height = 13
    Caption = 'Retenci'#243'n IIBB'
  end
  object Label15: TLabel
    Left = 363
    Top = 290
    Width = 72
    Height = 13
    Caption = 'Percepci'#243'n IVA'
  end
  object Label14: TLabel
    Left = 363
    Top = 264
    Width = 68
    Height = 13
    Caption = 'Retenci'#243'n IVA'
  end
  object Label13: TLabel
    Left = 394
    Top = 747
    Width = 114
    Height = 13
    Caption = 'Alicuota - Neto gravado'
    Visible = False
  end
  object Label12: TLabel
    Left = 26
    Top = 362
    Width = 40
    Height = 13
    Caption = 'NG 27%'
  end
  object Label11: TLabel
    Left = 27
    Top = 327
    Width = 50
    Height = 13
    Caption = 'NG 10,5%'
  end
  object Label10: TLabel
    Left = 26
    Top = 293
    Width = 40
    Height = 13
    Caption = 'NG 21%'
  end
  object Label9: TLabel
    Left = 362
    Top = 155
    Width = 20
    Height = 13
    Caption = 'Tipo'
  end
  object Label8: TLabel
    Left = 362
    Top = 121
    Width = 54
    Height = 13
    Caption = 'Documento'
  end
  object Label7: TLabel
    Left = 27
    Top = 236
    Width = 66
    Height = 13
    Caption = 'Cuenta venta'
  end
  object Label6: TLabel
    Left = 27
    Top = 202
    Width = 155
    Height = 13
    Caption = 'Pto de venta - Nro comprobante'
  end
  object Label5: TLabel
    Left = 362
    Top = 46
    Width = 33
    Height = 13
    Caption = 'Cliente'
  end
  object Label4: TLabel
    Left = 362
    Top = 19
    Width = 110
    Height = 13
    Caption = 'Fecha de comprobante'
  end
  object Label3: TLabel
    Left = 26
    Top = 161
    Width = 36
    Height = 13
    Caption = 'Per'#237'odo'
  end
  object Label2: TLabel
    Left = 26
    Top = 103
    Width = 69
    Height = 13
    Caption = 'Contribuyente'
  end
  object desTipo: TLabel
    Left = 529
    Top = 155
    Width = 4
    Height = 13
    Caption = '-'
  end
  object desDocumento: TLabel
    Left = 529
    Top = 121
    Width = 4
    Height = 13
    Caption = '-'
  end
  object desCuentaVenta: TLabel
    Left = 180
    Top = 236
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Label1: TLabel
    Left = 234
    Top = 203
    Width = 4
    Height = 13
    Caption = '-'
  end
  object desAlicuota4: TLabel
    Left = 324
    Top = 796
    Width = 35
    Height = 13
    AutoSize = False
    Caption = '21%'
    Visible = False
  end
  object desAlicuota3: TLabel
    Left = 325
    Top = 769
    Width = 35
    Height = 13
    AutoSize = False
    Caption = '21%'
    Visible = False
  end
  object desAlicuota2: TLabel
    Left = 325
    Top = 742
    Width = 35
    Height = 13
    AutoSize = False
    Caption = '21%'
    Visible = False
  end
  object desAlicuota1: TLabel
    Left = 325
    Top = 715
    Width = 35
    Height = 13
    AutoSize = False
    Caption = '21%'
    Visible = False
  end
  object desCliente: TLabel
    Left = 488
    Top = 70
    Width = 4
    Height = 13
    Caption = '-'
  end
  object desContribuyente: TLabel
    Left = 141
    Top = 130
    Width = 4
    Height = 13
    Caption = '-'
  end
  object LabIVA1: TLabel
    Left = 233
    Top = 293
    Width = 70
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = '$ 0,00'
  end
  object LabIVA2: TLabel
    Left = 232
    Top = 327
    Width = 70
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = '$ 0,00'
  end
  object LabIVA3: TLabel
    Left = 233
    Top = 362
    Width = 70
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = '$ 0,00'
  end
  object LabIVA4: TLabel
    Left = 454
    Top = 796
    Width = 31
    Height = 13
    Caption = '$ 0,00'
    Visible = False
  end
  object Label23: TLabel
    Left = 233
    Top = 266
    Width = 70
    Height = 14
    Alignment = taCenter
    AutoSize = False
    Caption = 'IVA'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  object Label24: TLabel
    Left = 362
    Top = 189
    Width = 54
    Height = 13
    Caption = 'Jurisdiccion'
  end
  object desJurisdiccion: TLabel
    Left = 529
    Top = 189
    Width = 4
    Height = 13
    Caption = '-'
  end
  object Bevel1: TBevel
    Left = 24
    Top = 274
    Width = 277
    Height = 10
    Shape = bsBottomLine
  end
  object Bevel2: TBevel
    Left = 24
    Top = 317
    Width = 277
    Height = 2
    Shape = bsBottomLine
  end
  object Bevel3: TBevel
    Left = 24
    Top = 351
    Width = 277
    Height = 2
    Shape = bsBottomLine
  end
  object Bevel4: TBevel
    Left = 26
    Top = 386
    Width = 277
    Height = 2
    Shape = bsBottomLine
  end
  object btMostrarComp: TSpeedButton
    Left = 195
    Top = 158
    Width = 23
    Height = 22
    Glyph.Data = {
      76050000424D7605000000000000360000002800000015000000150000000100
      1800000000004005000074120000741200000000000000000000E5E3E2E6E4E2
      E6E4E2E6E5E3E7E5E3E7E5E4E7E6E4E8E6E4E8E6E5E8E7E5E9E7E5E9E8E6E9E8
      E6EAE8E7EAE9E7EAE9E7F4F2F1DFDEDD61616567676BEDEBEA00E7E5E3E7E5E3
      E7E6E4E8E6E4E8E6E4E8E7E5E9E7E5E9E7E6E9E8E6EAE8E6EAE8E7EAE9E7EBE9
      E8EBE9E8EBEAE8F6F5F3D9D8D72C2C3239393E3333396E6D7100E8E6E4E8E6E4
      E8E7E5E9E7E5E9E7E6E9E8E6EAE8E6EAE8E7EAE9E7EBE9E8EBE9E8EBEAE8ECEA
      E9ECEBE9F8F6F4D5D4D42B2B313D3D4240404539393E66666A00E9E7E5E9E7E6
      E9E8E6EAE8E6EAE8E7EAE9E7EBE9E8EDECEAEEEDEBEDEBEAECEBE9ECEBEAEDEB
      EAF9F8F6D2D1D02A2A303E3E434040453D3D422C2C32E2E1E000EAE8E7EAE8E7
      EAE9E7EBE9E8F0EFEDFAF9F6FFFEFCE9E7E6E3E2E1FBF9F8FFFEFCF6F5F3FBFA
      F8CDCCCD29292F3E3E434040453C3C412E2E34E2E1E0FAF8F700EBE9E8EBEAE8
      ECEBE9FEFCFAD4D2D26D6D713031362B2B312C2C3229292F535358B1B1B2CECD
      CD28292E3E3E434040453C3C41303036E7E6E5FAF9F8F2F1F000ECEAE9EDECEA
      FFFFFF7C7B7E27272D38383E3E3E434040454040453F3F443B3B403333383031
      363F3F444040453B3B40323238EBEAEAFAF9F8F2F1F0F3F2F100EDECEAFFFFFF
      6565683030363F3F443C3C423232372C2C312A2A302F2F3538383E4040454040
      454040453D3D4235353BF0EFEEFAF9F8F3F2F1F3F2F2F4F3F200F9F8F6A09FA1
      2D2D3340404537373D414146B8B8B9F3F2F1FDFCFAD5D4D46E6D712C2C323F3F
      443F3F44303035FBFAF9FAFAF9F4F3F2F4F3F2F4F4F3F5F4F300FEFCFB2E2E33
      3E3E43393A3F555559FFFFFFFAF9F8F4F3F2F3F2F1F8F7F5FFFFFFA5A4A62D2D
      323F3F44313136BDBCBDFDFCFBF5F4F3F5F4F4F5F5F4F6F5F400BAB9BA303136
      3F3F442E2E34FCFBF9F5F4F3F2F1F0F2F2F1F3F2F1F3F2F1F3F3F2FFFFFF6969
      6D39393E39393F626266FFFFFFF6F5F4F6F6F5F6F6F5F7F6F6008C8C8E37373C
      38383D7A7A7DFFFFFFF3F2F1F3F2F1F4F3F2F4F3F2F4F3F3F5F4F3FBFBFAD0D0
      D02F2F353E3E43303035FFFFFFF7F6F6F7F7F6F7F7F6F8F7F70079797C39393E
      343439A3A2A4FEFEFCF4F3F2F4F4F3F5F4F3F5F4F3F5F4F4F6F5F4F9F8F7F7F7
      F62B2B3140404529292EFFFFFEF9F9F8F8F8F7F9F8F8F9F9F800807F8238383D
      35353A99989BFFFFFFF5F4F4F5F5F4F6F5F4F6F5F5F6F6F5F7F6F5FBFAFAEEEE
      ED2C2C323F3F4428282EFFFFFFFAF9F9F9F9F9FAF9F9FAFAF9009F9EA135353A
      3B3B40555559FFFFFFF6F5F5F6F6F5F7F6F5F7F6F6F7F7F6F8F7F7FFFFFFB0AF
      B13232383D3D42414145FFFFFFFAFAF9FAFAFAFBFAFAFBFBFA00E0DFDF29292F
      3F3F442C2C32C5C4C6FFFFFFF7F7F6F8F7F7F8F8F7F8F8F7FEFDFDFFFFFF3939
      3E3D3D4236363B858588FFFFFFFBFBFBFBFBFBFCFCFBFCFCFC00FFFFFF535357
      3A3A3F3F3F442C2C31C4C4C5FFFFFFFFFFFFFFFFFFFFFFFFFCFBFB4B4B4F3939
      3E3F3F4425252AF2F2F2FFFFFFFCFCFCFDFCFCFDFDFDFDFDFD00FCFBFBEDECEC
      26262C3E3E433F3F442C2C32525257969799A0A0A37373762A2A303B3B404040
      452B2B3198989BFFFFFFFDFDFDFDFDFDFEFEFDFEFEFEFEFEFE00F9F8F8FFFFFF
      D1D1D225252B3A3A3F4040453B3B4035353A34343938383D3F3F443E3E432929
      2E7B7A7EFFFFFFFEFEFEFEFEFEFEFEFEFFFFFFFFFFFFFFFFFF00FAF9F9FAFAF9
      FFFFFFEEEEEE52525628282E34343938383D38383D36363B2E2E34303035B6B6
      B8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FBFAFAFBFBFB
      FBFBFBFFFFFFFFFFFFE4E4E5A3A2A58383867E7E82949496C9C9CAFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00}
    OnClick = btMostrarCompClick
  end
  object SpeedButton1: TSpeedButton
    Left = 115
    Top = 233
    Width = 20
    Height = 21
    Caption = '+'
    OnClick = SpeedButton1Click
  end
  object EdAlicuota2: TEdit
    Left = 270
    Top = 739
    Width = 49
    Height = 21
    Alignment = taCenter
    Enabled = False
    NumbersOnly = True
    TabOrder = 31
    Text = '1'
    Visible = False
    OnExit = EdAlicuota2Exit
    OnMouseUp = EdAlicuota2MouseUp
  end
  object BtnAgregarYCont: TButton
    Left = 191
    Top = 497
    Width = 166
    Height = 25
    Caption = 'Guardar y cargar otro'
    TabOrder = 25
    OnClick = BtnAgregarYContClick
  end
  object BtnCancelar: TButton
    Left = 363
    Top = 497
    Width = 166
    Height = 25
    Caption = 'Cancelar cambios'
    TabOrder = 26
    OnClick = BtnCancelarClick
    OnExit = BtnCancelarExit
  end
  object BtnAgregarComp: TButton
    Left = 19
    Top = 497
    Width = 166
    Height = 25
    Caption = 'Guardar'
    TabOrder = 24
    OnClick = BtnAgregarCompClick
  end
  object EdTipo: TEdit
    Left = 487
    Top = 152
    Width = 33
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 11
    OnExit = EdTipoExit
    OnKeyPress = EdTipoKeyPress
    OnMouseUp = EdTipoMouseUp
  end
  object EdDocumento: TEdit
    Left = 487
    Top = 118
    Width = 33
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 10
    OnExit = EdDocumentoExit
    OnKeyPress = EdDocumentoKeyPress
    OnMouseUp = EdDocumentoMouseUp
  end
  object EdAlicuota4: TEdit
    Left = 270
    Top = 793
    Width = 49
    Height = 21
    Alignment = taCenter
    Enabled = False
    NumbersOnly = True
    TabOrder = 33
    Text = '1'
    Visible = False
    OnExit = EdAlicuota4Exit
    OnMouseUp = EdAlicuota4MouseUp
  end
  object EdAlicuota3: TEdit
    Left = 270
    Top = 766
    Width = 49
    Height = 21
    Alignment = taCenter
    Enabled = False
    NumbersOnly = True
    TabOrder = 32
    Text = '1'
    Visible = False
    OnExit = EdAlicuota3Exit
    OnMouseUp = EdAlicuota3MouseUp
  end
  object EdAlicuota1: TEdit
    Left = 270
    Top = 712
    Width = 49
    Height = 21
    Alignment = taCenter
    Enabled = False
    NumbersOnly = True
    TabOrder = 30
    Text = '1'
    Visible = False
    OnExit = EdAlicuota1Exit
    OnMouseUp = EdAlicuota1MouseUp
  end
  object EdFecha: TEdit
    Left = 487
    Top = 16
    Width = 65
    Height = 21
    TabOrder = 3
    Text = '__/__/____'
    OnExit = EdFechaExit
    OnKeyDown = EdFechaKeyDown
    OnKeyPress = EdFechaKeyPress
    OnKeyUp = EdFechaKeyUp
    OnMouseUp = EdFechaMouseUp
  end
  object EdTotal: TEdit
    Left = 488
    Top = 410
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 28
    Text = '$ 0,00'
    OnEnter = EdTotalEnter
    OnExit = EdTotalExit
    OnKeyPress = EdTotalKeyPress
    OnMouseUp = EdTotalMouseUp
  end
  object EdExentos: TEdit
    Left = 141
    Top = 450
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 17
    Text = '$ 0,00'
    OnEnter = EdExentosEnter
    OnExit = EdExentosExit
    OnKeyPress = EdExentosKeyPress
    OnMouseUp = EdExentosMouseUp
  end
  object EdConcNoGravados: TEdit
    Left = 141
    Top = 413
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 16
    Text = '$ 0,00'
    OnEnter = EdConcNoGravadosEnter
    OnExit = EdConcNoGravadosExit
    OnKeyPress = EdConcNoGravadosKeyPress
    OnMouseUp = EdConcNoGravadosMouseUp
  end
  object EdCuentaVenta: TEdit
    Left = 141
    Top = 233
    Width = 33
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    ParentShowHint = False
    ShowHint = False
    TabOrder = 9
    OnExit = EdCuentaVentaExit
    OnKeyPress = EdCuentaVentaKeyPress
    OnMouseUp = EdCuentaVentaMouseUp
  end
  object EdRetencionesGanancias: TEdit
    Left = 488
    Top = 369
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 22
    Text = '$ 0,00'
    OnEnter = EdRetencionesGananciasEnter
    OnExit = EdRetencionesGananciasExit
    OnKeyPress = EdRetencionesGananciasKeyPress
    OnMouseUp = EdRetencionesGananciasMouseUp
  end
  object EdPercepcionesIB: TEdit
    Left = 487
    Top = 342
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 21
    Text = '$ 0,00'
    OnEnter = EdPercepcionesIBEnter
    OnExit = EdPercepcionesIBExit
    OnKeyPress = EdPercepcionesIBKeyPress
    OnMouseUp = EdPercepcionesIBMouseUp
  end
  object EdRetencionesIB: TEdit
    Left = 487
    Top = 315
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 20
    Text = '$ 0,00'
    OnEnter = EdRetencionesIBEnter
    OnExit = EdRetencionesIBExit
    OnKeyPress = EdRetencionesIBKeyPress
    OnMouseUp = EdRetencionesIBMouseUp
  end
  object EdPercepcionesIVA: TEdit
    Left = 487
    Top = 288
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 19
    Text = '$ 0,00'
    OnEnter = EdPercepcionesIVAEnter
    OnExit = EdPercepcionesIVAExit
    OnKeyPress = EdPercepcionesIVAKeyPress
    OnMouseUp = EdPercepcionesIVAMouseUp
  end
  object EdRetencionesIVA: TEdit
    Left = 487
    Top = 261
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 18
    Text = '$ 0,00'
    OnEnter = EdRetencionesIVAEnter
    OnExit = EdRetencionesIVAExit
    OnKeyPress = EdRetencionesIVAKeyPress
    OnMouseUp = EdRetencionesIVAMouseUp
  end
  object EdNetoGravado4: TEdit
    Left = 362
    Top = 793
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 34
    Text = '$ 0,00'
    Visible = False
    OnEnter = EdNetoGravado4Enter
    OnExit = EdNetoGravado4Exit
    OnKeyPress = EdNetoGravado4KeyPress
    OnMouseUp = EdNetoGravado4MouseUp
  end
  object EdNetoGravado3: TEdit
    Left = 141
    Top = 359
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 15
    Text = '$ 0,00'
    OnEnter = EdNetoGravado3Enter
    OnExit = EdNetoGravado3Exit
    OnKeyPress = EdNetoGravado3KeyPress
    OnMouseUp = EdNetoGravado3MouseUp
  end
  object EdNetoGravado2: TEdit
    Left = 141
    Top = 324
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 14
    Text = '$ 0,00'
    OnEnter = EdNetoGravado2Enter
    OnExit = EdNetoGravado2Exit
    OnKeyPress = EdNetoGravado2KeyPress
    OnMouseUp = EdNetoGravado2MouseUp
  end
  object EdNetoGravado1: TEdit
    Left = 141
    Top = 290
    Width = 70
    Height = 21
    Alignment = taRightJustify
    TabOrder = 13
    Text = '$ 0,00'
    OnEnter = EdNetoGravado1Enter
    OnExit = EdNetoGravado1Exit
    OnKeyPress = EdNetoGravado1KeyPress
    OnMouseUp = EdNetoGravado1MouseUp
  end
  object EdNroComprobante: TEdit
    Left = 244
    Top = 200
    Width = 73
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 8
    Text = '00000000'
    OnExit = EdNroComprobanteExit
    OnMouseUp = EdNroComprobanteMouseUp
  end
  object EdPtoVenta: TEdit
    Left = 187
    Top = 200
    Width = 40
    Height = 21
    Alignment = taCenter
    NumbersOnly = True
    TabOrder = 7
    Text = '0000'
    OnExit = EdPtoVentaExit
    OnMouseUp = EdPtoVentaMouseUp
  end
  object EdPeriodo: TEdit
    Left = 141
    Top = 158
    Width = 48
    Height = 21
    MaxLength = 7
    NumbersOnly = True
    ParentShowHint = False
    ShowHint = False
    TabOrder = 2
    Text = '__/____'
    OnExit = EdPeriodoExit
    OnKeyDown = EdPeriodoKeyDown
    OnKeyPress = EdPeriodoKeyPress
    OnKeyUp = EdPeriodoKeyUp
    OnMouseUp = EdPeriodoMouseUp
  end
  object EdContribuyente: TEdit
    Left = 141
    Top = 103
    Width = 85
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 1
    Text = '__-________-_'
    OnExit = EdContribuyenteExit
    OnKeyDown = EdContribuyenteKeyDown
    OnKeyPress = EdContribuyenteKeyPress
    OnKeyUp = EdContribuyenteKeyUp
    OnMouseUp = EdContribuyenteMouseUp
  end
  object EdCliente: TEdit
    Left = 487
    Top = 43
    Width = 85
    Height = 21
    MaxLength = 13
    NumbersOnly = True
    TabOrder = 5
    Text = '__-________-_'
    OnExit = EdClienteExit
    OnKeyDown = EdClienteKeyDown
    OnKeyPress = EdClienteKeyPress
    OnKeyUp = EdClienteKeyUp
    OnMouseUp = EdClienteMouseUp
  end
  object ChAnulado: TCheckBox
    Left = 363
    Top = 449
    Width = 141
    Height = 17
    Caption = 'Comprobante anulado'
    TabOrder = 23
  end
  object AgCliente: TButton
    Left = 578
    Top = 43
    Width = 21
    Height = 21
    Caption = '+'
    TabOrder = 6
    OnClick = AgClienteClick
  end
  object EdJurisdiccion: TEdit
    Left = 487
    Top = 186
    Width = 33
    Height = 21
    Alignment = taCenter
    TabOrder = 12
    OnExit = EdJurisdiccionExit
    OnKeyPress = EdJurisdiccionKeyPress
    OnMouseUp = EdJurisdiccionMouseUp
  end
  object RG1: TRadioGroup
    Left = 26
    Top = 19
    Width = 154
    Height = 78
    Caption = 'Tipo de comprobante'
    ItemIndex = 0
    Items.Strings = (
      'Comprobante venta'
      'Tique Z')
    TabOrder = 29
    OnClick = RG1Click
  end
  object btEliminarComp: TButton
    Left = 535
    Top = 497
    Width = 166
    Height = 25
    Caption = 'Eliminar este comprobante'
    TabOrder = 27
    OnClick = btEliminarCompClick
    OnExit = btEliminarCompExit
  end
  object Edit1: TEdit
    Left = 110
    Top = 103
    Width = 25
    Height = 21
    TabOrder = 0
    OnExit = Edit1Exit
  end
  object Edit2: TEdit
    Left = 457
    Top = 43
    Width = 25
    Height = 21
    TabOrder = 4
    OnExit = Edit2Exit
  end
  object AuxQuery: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 552
    Top = 792
  end
  object SQLQuery1: TSQLQuery
    MaxBlobSize = -1
    Params = <>
    SQLConnection = SQLConnection1
    Left = 552
    Top = 720
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
    Top = 736
  end
  object DataSetProvider1: TDataSetProvider
    DataSet = SQLQuery1
    Left = 824
    Top = 736
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    Params = <>
    ProviderName = 'DataSetProvider1'
    Left = 696
    Top = 736
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 760
    Top = 736
  end
end
