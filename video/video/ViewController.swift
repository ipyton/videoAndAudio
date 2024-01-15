//
//  ViewController.swift
//  video
//
//  Created by chen on 2024/1/15.
//

import Cocoa

class ViewController: NSViewController {
    //this is a demo to show button usage.
    
    var recStatus: Bool = false;
    var thread: Thread?
    let cmdButton = NSButton.init(title:"", target: nil, action: nil)
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let w_width = 320
        let w_height = 240
        let o_x:Int = 320/2 - 40
        let o_y:Int = 240/2 - 15
        
        self.view.setFrameSize(NSSize(width: w_width, height: w_height))
        
        cmdButton.frame = NSRect(x: o_x, y: o_y, width: 80, height: 30)
        cmdButton.title = "record"
        cmdButton.setButtonType(.pushOnPushOff)
        cmdButton.target = self
        cmdButton.action = #selector(self.myfunc)
        cmdButton.bezelStyle = .rounded
        self.view.addSubview(cmdButton)
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
    
    @objc func myfunc() {
        print("helloworld")
    }
    
    @objc func recAudio() {
        
    }

}

