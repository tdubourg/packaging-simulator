/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package IHM;

import client.Command;
import client.ThreadLog;
import java.awt.Dialog;

/**
 *
 * @author Elodie
 */
public class ManagementFrame extends javax.swing.JFrame {

    Command threadCmd;
    ThreadLog threadLog;
    String lot;
    
    //disponibilité warehouse
    int palA;
    int palB;

    public int getPalA() {
        return palA;
    }

    public int getPalB() {
        return palB;
    }
    
    /**
     * Creates new form ManagementFrame
     */
    public ManagementFrame(Command threadCmd, ThreadLog threadLog, String lot) {
            initComponents();
            this.threadCmd = threadCmd;
            this.threadLog = threadLog;
            this.lot = lot;
            this.descriptionLabel.setText("Etat de fabrication du lot" + lot);
            this.palA=0;
            this.palB=0;
    }

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        descriptionLabel = new javax.swing.JLabel();
        newCmdButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Suivi de la chaine de production");
        setResizable(false);

        descriptionLabel.setText("Etat de fabrication du lot");

        newCmdButton.setText("Nouvelle commande");
        newCmdButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                newCmdButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(descriptionLabel)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(230, Short.MAX_VALUE)
                .addComponent(newCmdButton, javax.swing.GroupLayout.PREFERRED_SIZE, 147, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(218, 218, 218))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(descriptionLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 334, Short.MAX_VALUE)
                .addComponent(newCmdButton)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void newCmdButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_newCmdButtonActionPerformed
        NewCmdFrame newCmd = new NewCmdFrame(this, this.threadCmd);
        newCmd.setVisible(true);
    }//GEN-LAST:event_newCmdButtonActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel descriptionLabel;
    private javax.swing.JButton newCmdButton;
    // End of variables declaration//GEN-END:variables
}
