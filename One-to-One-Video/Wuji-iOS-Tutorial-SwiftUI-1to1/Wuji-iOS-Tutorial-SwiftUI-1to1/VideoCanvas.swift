//
//  VideoView.swift
//  Wuji-iOS-Tutorial-SwiftUI-1to1
//
//  Created by 3 on 2020/12/17.
//  Portions Copyright (c) 2020 wuji-co. All rights reserved.
//

import SwiftUI

struct VideoCanvas : UIViewRepresentable {
    let rendererView = UIView()
    
    func makeUIView(context: Context) -> UIView {
        rendererView.backgroundColor = UIColor.gray
        return rendererView
    }
    
    func updateUIView(_ uiView: UIView, context: Context) { }
}

struct VideoView_Previews : PreviewProvider {
    static var previews: some View {
        VideoCanvas()
    }
}
