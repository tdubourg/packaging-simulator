/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package IHM;

import client.Command;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;

/**
 *
 * @author
 * Theo
 */
public class GameOverPopup extends javax.swing.JFrame {

	private ParametersFrame paramsFrame;

        /**
         * Sets the frame's parameters
         * @param j parameters
         */
	public void setParamsFrame(ParametersFrame j) {
		this.paramsFrame = j;
	}

	/**
	 * Creates new form GameOverPopup
	 */
	public GameOverPopup() {
		initComponents();
	}

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jB_NewProd = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        jB_Shutdown = new javax.swing.JButton();
        jB_CommandOnlyMode = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jB_NewProd.setText("Nouveau lot");
        jB_NewProd.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jB_NewProdActionPerformed(evt);
            }
        });

        jLabel1.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        jLabel1.setText("La production s'est terminée.");

        jB_Shutdown.setText("Terminer définitivement la production");
        jB_Shutdown.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jB_ShutdownActionPerformed(evt);
            }
        });

        jB_CommandOnlyMode.setText("Passer en mode \"Commandes uniquement\"");
        jB_CommandOnlyMode.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jB_CommandOnlyModeActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jB_NewProd, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jB_CommandOnlyMode, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(jB_Shutdown, javax.swing.GroupLayout.DEFAULT_SIZE, 339, Short.MAX_VALUE)
                    .addContainerGap()))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, 86, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jB_NewProd, javax.swing.GroupLayout.PREFERRED_SIZE, 54, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jB_CommandOnlyMode, javax.swing.GroupLayout.PREFERRED_SIZE, 54, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(76, 76, 76))
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                    .addContainerGap(236, Short.MAX_VALUE)
                    .addComponent(jB_Shutdown, javax.swing.GroupLayout.PREFERRED_SIZE, 54, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(10, 10, 10)))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

	private Command command;

        /**
         * Sets the command
         * @param c command
         */
	public void setCommand(Command c) {
		this.command = c;
	}
	
        /**
         * New production after clicking on button "nouveau lot"
         * @param evt click on button "nouveau lot"
         */
    private void jB_NewProdActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jB_NewProdActionPerformed
		this.paramsFrame.show();
		this.hide();
    }//GEN-LAST:event_jB_NewProdActionPerformed

    /**
     * Shutdown client and server after cliking on button "Terminer..."
     * @param evt click on button "Terminer définitivement la production" 
     */
    private void jB_ShutdownActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jB_ShutdownActionPerformed
		this.command.sendShutdown();
		try {
			Thread.sleep(10 * 1000);//* Wait for server to shutdown...
		} catch (InterruptedException ex) {
			Logger.getLogger(ErrorPopup.class.getName()).log(Level.SEVERE, null, ex);
		}
		System.exit(0);//* Shutdown the client app
    }//GEN-LAST:event_jB_ShutdownActionPerformed

    private void jB_CommandOnlyModeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jB_CommandOnlyModeActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jB_CommandOnlyModeActionPerformed

	/**
	 * @param args the command line arguments
	 */
	public static void main(String args[]) {
		/* Set the Nimbus look and feel */
		//<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
		 * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
		 */
		try {
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (ClassNotFoundException ex) {
			java.util.logging.Logger.getLogger(GameOverPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (InstantiationException ex) {
			java.util.logging.Logger.getLogger(GameOverPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (IllegalAccessException ex) {
			java.util.logging.Logger.getLogger(GameOverPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		} catch (javax.swing.UnsupportedLookAndFeelException ex) {
			java.util.logging.Logger.getLogger(GameOverPopup.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
		}
		//</editor-fold>

		/* Create and display the form */
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				new GameOverPopup().setVisible(true);
			}
		});
	}
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jB_CommandOnlyMode;
    private javax.swing.JButton jB_NewProd;
    private javax.swing.JButton jB_Shutdown;
    private javax.swing.JLabel jLabel1;
    // End of variables declaration//GEN-END:variables
}
