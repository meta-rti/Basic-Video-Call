//
//  WJEVideoConstraints.swift
//  VideoViews
//
//  Created by 3 on 2020/12/16.
//  Copyright © 2020年 Wuji. All rights reserved.
//

#if os(iOS)
import UIKit
#else
import Cocoa
#endif

class WJEVideoConstraints: NSObject {
    
}

// MARK: - Public API
extension WJEVideoConstraints {
    static func add(for subView: WJEView, on superView: WJEView, startPoint: CGPoint, whSize: WJEVideoLayout.ConstraintsType, needAddSubView: Bool = true) -> [NSLayoutConstraint] {
        if needAddSubView {
            subView.removeFromSuperview()
        }
        
        subView.translatesAutoresizingMaskIntoConstraints = false
        
        if needAddSubView {
            superView.addSubview(subView)
        }
        
        var constraints = [NSLayoutConstraint]()
        
        let ltConstraints = add(for: subView,
                                on: superView,
                                startPoint: startPoint)
        constraints.append(contentsOf: ltConstraints)
        
        switch whSize {
        case .scale(let value):
            let whConstraints = add(for: subView,
                                   on: superView,
                                   widthScale: value.width,
                                   heightScale: value.height)
            constraints.append(contentsOf: whConstraints)
        case .constant(let value):
            let whConstraints = add(for: subView,
                                    on: superView,
                                    width: value.width,
                                    height: value.height)
            constraints.append(contentsOf: whConstraints)
        }
        
        return constraints
    }
    
    static func add(for itemViews: [WJEView], on superView: WJEView, rankRow: WJERankRow, whSize: WJEVideoLayout.ConstraintsType, interitemSpacing: CGFloat, lineSpacing: CGFloat) -> [NSLayoutConstraint] {
        var constraints = [NSLayoutConstraint]()
        var lastView: WJEView?
        
        for row in 0..<rankRow.rows where row < itemViews.count {
            var index: Int = 0
            guard index < itemViews.count else {
                break
            }
            
            for rank in 0..<rankRow.ranks {
                index = row * rankRow.ranks + rank
                
                guard index < itemViews.count else {
                    break
                }
                
                let view = itemViews[index]
                view.removeFromSuperview()
                view.translatesAutoresizingMaskIntoConstraints = false
                superView.addSubview(view)
                
                // first rank view of per rows
                if rank == 0 {
                    let left = NSLayoutConstraint(item: view,
                                                  attribute: .left,
                                                  relatedBy: .equal,
                                                  toItem: superView,
                                                  attribute: .left,
                                                  multiplier: 1,
                                                  constant: 0)
                    constraints.append(left)
                    
                    if row == 0 {
                        let top = NSLayoutConstraint(item: view,
                                                     attribute: .top,
                                                     relatedBy: .equal,
                                                     toItem: superView,
                                                     attribute: .top,
                                                     multiplier: 1,
                                                     constant: 0)
                        constraints.append(top)
                    } else {
                        let lastRowIndex = index - rankRow.ranks
                        let last = lastRowIndex < 0 ? 0 : lastRowIndex
                        let lastRowView = itemViews[last]
                        let top = NSLayoutConstraint(item: lastRowView,
                                                     attribute: .bottom,
                                                     relatedBy: .equal,
                                                     toItem: view,
                                                     attribute: .top,
                                                     multiplier: 1,
                                                     constant: -lineSpacing)
                        constraints.append(top)
                    }
                } else if let lastView = lastView {
                    let left = NSLayoutConstraint(item: view,
                                                  attribute: .left,
                                                  relatedBy: .equal,
                                                  toItem: lastView,
                                                  attribute: .right,
                                                  multiplier: 1,
                                                  constant: interitemSpacing)
                    constraints.append(left)
                    
                    let top = NSLayoutConstraint(item: view,
                                                 attribute: .top,
                                                 relatedBy: .equal,
                                                 toItem: lastView,
                                                 attribute: .top,
                                                 multiplier: 1,
                                                 constant: 0)
                    constraints.append(top)
                }
                
                switch whSize {
                case .scale(let value):
                    let whConstraints = add(for: view,
                                            on: superView,
                                            widthScale: value.width,
                                            heightScale: value.height)
                    constraints.append(contentsOf: whConstraints)
                case .constant(let value):
                    let whConstraints = add(for: view,
                                            on: superView,
                                            width: value.width,
                                            height: value.height)
                    constraints.append(contentsOf: whConstraints)
                }
                
                lastView = view
            }
        }
        return constraints
    }
}

// MARK: - Scale Constraints
fileprivate extension WJEVideoConstraints {
    static func add(for subView: WJEView, on superView: WJEView, widthScale: CGFloat, heightScale: CGFloat) -> [NSLayoutConstraint] {
        subView.translatesAutoresizingMaskIntoConstraints = false
        var constraints = [NSLayoutConstraint]()
        
        let width = NSLayoutConstraint(item: subView,
                                       attribute: .width,
                                       relatedBy: .equal,
                                       toItem: superView,
                                       attribute: .width,
                                       multiplier: widthScale,
                                       constant: 0)
        constraints.append(width)
        
        let height = NSLayoutConstraint(item: subView,
                                        attribute: .height,
                                        relatedBy: .equal,
                                        toItem: superView,
                                        attribute: .height,
                                        multiplier: heightScale,
                                        constant: 0)
        constraints.append(height)
        return constraints
    }
}

// MARK: - Constant Constraints
fileprivate extension WJEVideoConstraints {
    static func add(for subView: WJEView, on superView: WJEView, startPoint: CGPoint) -> [NSLayoutConstraint] {
        subView.translatesAutoresizingMaskIntoConstraints = false
        var constraints = [NSLayoutConstraint]()

        let left = NSLayoutConstraint(item: subView,
                                      attribute: .left,
                                      relatedBy: .equal,
                                      toItem: superView,
                                      attribute: .left,
                                      multiplier: 1,
                                      constant: startPoint.x)
        constraints.append(left)

        let top = NSLayoutConstraint(item: subView,
                                     attribute: .top,
                                     relatedBy: .equal,
                                     toItem: superView,
                                     attribute: .top,
                                     multiplier: 1,
                                     constant: startPoint.y)
        constraints.append(top)
        
        return constraints
    }
    
    static func add(for subView: WJEView, on superView: WJEView, width: CGFloat, height: CGFloat) -> [NSLayoutConstraint] {
        subView.translatesAutoresizingMaskIntoConstraints = false
        var constraints = [NSLayoutConstraint]()
        
        let width = NSLayoutConstraint(item: subView,
                                       attribute: .width,
                                       relatedBy: .equal,
                                       toItem: nil,
                                       attribute: .notAnAttribute,
                                       multiplier: 0.0,
                                       constant: width)
        constraints.append(width)
        
        let height = NSLayoutConstraint(item: subView,
                                        attribute: .height,
                                        relatedBy: .equal,
                                        toItem: nil,
                                        attribute: .notAnAttribute,
                                        multiplier: 0.0,
                                        constant: height)
        
        constraints.append(height)
        
        return constraints
    }
}
