/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package IHM;

import client.Command;
import client.ThreadLog;
import java.io.IOException;
import java.net.ConnectException;
import javax.swing.JProgressBar;

/**
 *
 * @author
 * Elodie
 */
public class WelcomeFrame extends javax.swing.JFrame {

	/**
	 * Creates
	 * new
	 * form
	 * WelcomeFrame
	 */
	public WelcomeFrame() {
		initComponents();
		waitingMessage.setVisible(false);
	}

	/**
	 * This
	 * method
	 * is
	 * called
	 * from
	 * within
	 * the
	 * constructor
	 * to
	 * initialize
	 * the
	 * form.
	 * WARNING:
	 * Do
	 * NOT
	 * modify
	 * this
	 * code.
	 * The
	 * content
	 * of
	 * this
	 * method
	 * is
	 * always
	 * regenerated
	 * by
	 * the
	 * Form
	 * Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        connectMessage = new javax.swing.JLabel();
        connectButton = new javax.swing.JButton();
        waitingMessage = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Connexion au serveur");
        setFocusCycleRoot(false);
        setResizable(false);

        connectMessage.setText("Veuillez vous connecter au serveur.");

        connectButton.setText("Connexion");
        connectButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                connectButtonActionPerformed(evt);
            }
        });

        waitingMessage.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        waitingMessage.setText("Connexion impossible : le serveur ne répond pas.");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(73, 73, 73)
                        .addComponent(connectMessage))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(114, 114, 114)
                        .addComponent(connectButton)))
                .addContainerGap(77, Short.MAX_VALUE))
            .addComponent(waitingMessage, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(41, 41, 41)
                .addComponent(connectMessage)
                .addGap(18, 18, 18)
                .addComponent(connectButton)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(waitingMessage, javax.swing.GroupLayout.DEFAULT_SIZE, 24, Short.MAX_VALUE)
                .addGap(18, 18, 18))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

	private void connectButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_connectButtonActionPerformed
		try {
			// création des threads
			Command threadCmd = new Command();
			ThreadLog threadLog = new ThreadLog();
			// activation des threads
			threadLog.start();

			ParametersFrame managerFrame = new ParametersFrame(threadCmd, threadLog);
			managerFrame.setVisible(true);
			this.dispose();
		} catch (IOException e) {
			this.waitingMessage.setVisible(true);
		}


	}//GEN-LAST:event_connectButtonActionPerformed

	/**
	 * @param
	 * args
	 * the
	 * command
	 * line
	 * arguments
	 */
	public static void main(String args[]) {
		/*
		 * Set the Nimbus look and feel
		 */
		//<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /*
		 * If Nimbus (introduced in Java SE 6) is not available, stay with the
		 * default look and feel. For details see
		 * http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
		 */
		try {
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (ClassNotFoundException ex) {
			java.util.logging.Logger.getLogger(WelcomeFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (InstantiationException ex) {
			java.util.logging.Logger.getLogger(WelcomeFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (IllegalAccessException ex) {
			java.util.logging.Logger.getLogger(WelcomeFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (javax.swing.UnsupportedLookAndFeelException ex) {
			java.util.logging.Logger.getLogger(WelcomeFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		//</editor-fold>

		/*
		 * Create and display the form
		 */
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				new WelcomeFrame().setVisible(true);
			}
		});
	}
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton connectButton;
    private javax.swing.JLabel connectMessage;
    private javax.swing.JLabel waitingMessage;
    // End of variables declaration//GEN-END:variables
}
